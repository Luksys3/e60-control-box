import { Button, ScrollView, Text, View } from "react-native";

import React, { useEffect, useRef, useState } from "react";
import {
	BleManager,
	Characteristic,
	Device,
	State,
} from "react-native-ble-plx";
import { SafeAreaView } from "react-native-safe-area-context";

export default function HomeScreen() {
	const [devices, setDevices] = useState<Device[]>([]);
	const [connecting, setConnecting] = useState(false);
	const [connectedDevice, setConnectedDevice] = useState<{
		device: Device;
		characteristic: Characteristic;
	} | null>(null);

	const blocked = useRef(false);

	const manager = useRef<BleManager | null>(null);

	useEffect(() => {
		manager.current = new BleManager();

		const subscription = manager.current.onStateChange((state) => {
			if (state === State.PoweredOn) {
				console.log("Bluetooth is ON, starting scan...");
				refreshDevices();
			}
		}, true);

		return () => {
			subscription.remove();
			manager.current?.destroy();
		};
	}, []);

	const refreshDevices = () => {
		manager.current?.stopDeviceScan();

		setDevices([]);

		manager.current?.startDeviceScan(
			null,
			{
				allowDuplicates: false,
			},
			(error, device) => {
				if (error) {
					console.error("Scan error:", error);
					return;
				}
				console.log("Found device:", device?.name, device?.id);

				if (
					!device ||
					device.name === null ||
					device.name?.trim() === ""
				) {
					return;
				}

				setDevices((previousDevices) => {
					return previousDevices.find(
						(existingDevice) => existingDevice.id === device.id
					)
						? previousDevices
						: [device, ...previousDevices];
				});

				if (
					device?.name === "=E60" &&
					!connecting &&
					!connectedDevice &&
					!blocked.current
				) {
					blocked.current = true;
					console.log("Connecting", device);
					connectToDevice(device);
				}
			}
		);
	};

	const connectToDevice = async (device: Device) => {
		setConnecting(true);
		try {
			const newDevice = await device.connect();

			await newDevice.discoverAllServicesAndCharacteristics();

			const services = await newDevice.services();
			const service = services[0];

			const characteristics = await newDevice.characteristicsForService(
				service.uuid
			);
			const characteristic = characteristics[0];

			console.log("services", services);
			console.log("characteristics", characteristics);

			setConnectedDevice({
				device: newDevice,
				characteristic,
			});
		} finally {
			setConnecting(false);
		}
	};

	const writeWithoutResponse = async (message: string) => {
		if (!connectedDevice) {
			return;
		}

		await connectedDevice.device.writeCharacteristicWithoutResponseForService(
			connectedDevice.characteristic.serviceUUID,
			connectedDevice.characteristic.uuid,
			btoa(message)
		);
	};

	return (
		<SafeAreaView>
			<ScrollView>
				<Button title="Refresh" onPress={refreshDevices} />

				<View
					style={{
						padding: 20,
					}}
				>
					{devices.map((device) => (
						<View key={device.id} style={{ marginBottom: 6 }}>
							<Text style={{ color: "white" }}>
								{device.name}
								{"\n"}({device.id})
							</Text>

							<Button
								title="Connect"
								onPress={() => connectToDevice(device)}
							/>
						</View>
					))}
				</View>

				{connectedDevice && (
					<View>
						<Text>
							Connected device: {connectedDevice.device.name}
						</Text>
						<View style={{ display: "flex", marginBottom: 6 }}>
							<Button
								title="Disconnect"
								onPress={async () => {
									await connectedDevice.device.cancelConnection();
									setConnectedDevice(null);
								}}
							/>
						</View>
						<View style={{ display: "flex", marginBottom: 6 }}>
							<Button
								title="Regulator ON"
								onPress={() => writeWithoutResponse("e")}
							/>
							<Button
								title="Regulator OFF"
								onPress={() => writeWithoutResponse("r")}
							/>
						</View>
						<View style={{ display: "flex" }}>
							<Button
								title="Underglow ON"
								onPress={() => writeWithoutResponse("t")}
							/>
							<Button
								title="Underglow OFF"
								onPress={() => writeWithoutResponse("y")}
							/>
						</View>
					</View>
				)}
			</ScrollView>
		</SafeAreaView>
	);
}
