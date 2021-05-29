// predkosc 400kHz
// adress b110100x -> 0x68 lub 0x69 (strona 36)
#define MPU_ADDR (0x68<<1)
I2C_HandleTypeDef hi2c1;

struct Data {
	float axis[3];
};

void mpuInit() {
	uint8_t data = 0;
	// ustawiamy taktowanie na wew oscylator 8MHz
	// wybudzamy MPU
	// wylaczamy tryb okresowy
	// wlaczamy termometr
    HAL_I2C_Mem_Write(&hi2c1, MPU_ADDR, 0x6B, 1, &data, 1, 100);

    data = 0x07;
    // ustawiamy dzielnik na taktowanie 1kHz
    // Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV) = 8000 / (1 + 7)
    HAL_I2C_Mem_Write(&hi2c1, MPU_ADDR, 0x19, 1, &data, 1, 100);

    // wylaczamy self-testy
    // ustawiamy zakres na 2G
    data = 0;
    HAL_I2C_Mem_Write(&hi2c1, MPU_ADDR, 0x1C, 1, &data, 1, 100);

    // wylaczamy self-testy
    // ustawiamy zakres na +- 250 stopni na sekunde
    data = 0;
    HAL_I2C_Mem_Write(&hi2c1, MPU_ADDR, 0x1B, 1, &data, 1, 100);
}



uint8_t mpuWHO() { // komenda WHO AM I
	  uint8_t data = 0;
	  HAL_I2C_Mem_Read(&hi2c1, MPU_ADDR, 0x75, 1, &data, 1, 100);
	  return data;
}

void mpuAccel(struct Data* result) {
	uint8_t data[6];

	HAL_I2C_Mem_Read(&hi2c1, MPU_ADDR, 0x3B, 1, data, 6, 100);

	// 2^15 (16 bit bez znaku) = 32768 --> zakres 0-32768
	// czyl -16384 do 16384

	for (int i = 0; i < 3; i++) {
		result->axis[i] = data[i<<1] << 8 | data[(i<<1)+1];
		result->axis[i] /= 16384;
	}
}
