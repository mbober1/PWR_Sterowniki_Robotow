SPI_HandleTypeDef hspi3;

void adxWrite(uint8_t addr, uint8_t data) {
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi3, &addr, 1, 1000);
	HAL_SPI_Transmit(&hspi3, &data, 1, 1000);
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);
}

void adxReadOne(uint8_t addr, uint8_t *data) {
//	addr &= ~(0x40);
	addr |= (0x80);
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi3, &addr, 1, 1000);
	HAL_SPI_Receive(&hspi3, data, 1, 1000);
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);
}

void adxReadMore(uint8_t addr, uint8_t *data, uint8_t size) {
	addr |= 0x40;
	addr |= (0x80);
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi3, &addr, 1, 1000);
	HAL_SPI_Receive(&hspi3, data, size, 1000);
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);
}

uint8_t adxID() { // komenda device ID

	uint8_t data;
	adxReadOne(0x0, &data);
//	addr &= ~(0x40);
//	addr |= (0x80);
//
//	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET); // rozpoczynamy transmisje
//	HAL_SPI_Transmit(&hspi3, &addr, 1, 1000); // prosimy o dane z adressu 0
//	HAL_SPI_Receive(&hspi3, &data, 1, 1000); // odbieramy dane
//	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET); // konczymy transmisje

	return data;
}

void adxInit() {
	adxWrite(0x31, 0x40);
}
