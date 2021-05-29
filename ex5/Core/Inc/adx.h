SPI_HandleTypeDef hspi3;

uint8_t adxID() { // komenda device ID
	uint8_t data;
	uint8_t addr = 0;
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET); // rozpoczynamy transmisje
	HAL_SPI_Transmit(&hspi3, &addr, 1, 100); // prosimy o dane z adressu 0
	HAL_SPI_Receive(&hspi3, &data, 1, 100); // odbieramy dane
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET); // konczymy transmisje

	return data;
}
