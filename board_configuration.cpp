#include "pch.h"
#include "board_overrides.h"

Gpio getCommsLedPin() {
	return Gpio::Unassigned;
}

Gpio getRunningLedPin() {
	return Gpio::Unassigned;
}

Gpio getWarningLedPin() {
	return Gpio::Unassigned;
}

static const brain_pin_e injPins[] = {
    Gpio::D7,
	Gpio::G9,
	Gpio::G10,
	Gpio::G11,
	Gpio::G12,
	Gpio::G13
};

static const brain_pin_e ignPins[] = {
	Gpio::D4,
	Gpio::D3,
	Gpio::C9,
	Gpio::C8,
	Gpio::C7,
	Gpio::G8
};

static void setInjectorPins() {
	//copyArray(engineConfiguration->injectionPins, injPins);
	engineConfiguration->injectionPins[0] = Gpio::D7;
	engineConfiguration->injectionPins[1] = Gpio::G9;
	engineConfiguration->injectionPins[2] = Gpio::G10;
	engineConfiguration->injectionPins[3] = Gpio::G11;
	engineConfiguration->injectionPins[4] = Gpio::G12;
	engineConfiguration->injectionPins[5] = Gpio::G13;
}

static void setIgnitionPins() {
	//copyArray(engineConfiguration->ignitionPins, ignPins);
	engineConfiguration->ignitionPins[0] = Gpio::D4;
	engineConfiguration->ignitionPins[1] = Gpio::D3;
	engineConfiguration->ignitionPins[2] = Gpio::C9;
	engineConfiguration->ignitionPins[3] = Gpio::C8;
	engineConfiguration->ignitionPins[4] = Gpio::C7;
	engineConfiguration->ignitionPins[5] = Gpio::G8;
}

static void setupSdCard() {
	engineConfiguration->sdCardSpiDevice = SPI_DEVICE_3;
	engineConfiguration->sdCardCsPin = Gpio::D2;

	engineConfiguration->is_enabled_spi_3 = true;
	engineConfiguration->spi3sckPin = Gpio::C10;
	engineConfiguration->spi3misoPin = Gpio::C11;
	engineConfiguration->spi3mosiPin = Gpio::C12;

	engineConfiguration->is_enabled_spi_1 = true;
	engineConfiguration->spi5sckPin = Gpio::F7;
	engineConfiguration->spi5misoPin = Gpio::F8;
	engineConfiguration->spi5mosiPin = Gpio::F9;
}


static void setupVbatt() {
	// 5.6k high side/10k low side = 1.56 ratio divider
	engineConfiguration->analogInputDividerCoefficient = 1.56f;

	// 82k high side/10k low side = 9.2
	engineConfiguration->vbattDividerCoeff = (92.0f / 10.0f);

	// Battery sense on PA7
	engineConfiguration->vbattAdcChannel = EFI_ADC_7;

	
}
static void setupCAN() {
	
	engineConfiguration->canTxPin = Gpio::D1;
	engineConfiguration->canRxPin = Gpio::D0;
	engineConfiguration->can2RxPin = Gpio::B12;
	engineConfiguration->can2TxPin = Gpio::B13;

	engineConfiguration->lps25BaroSensorScl = Gpio::B10;
	engineConfiguration->lps25BaroSensorSda = Gpio::B11;
	
}

static void setupDefaultSensorInputs() {
	// trigger inputs
	// Digital channel 1 as default - others not set
	engineConfiguration->triggerInputPins[0] = Gpio::E8;
	engineConfiguration->camInputs[0] = Gpio::Unassigned;

	engineConfiguration->triggerInputPins[1] = Gpio::Unassigned;


	engineConfiguration->clt.adcChannel = EFI_ADC_12;
	engineConfiguration->iat.adcChannel = EFI_ADC_14;
	engineConfiguration->tps1_1AdcChannel = EFI_ADC_0;
	engineConfiguration->map.sensor.hwChannel = EFI_ADC_11;

    // see also enableAemXSeries
	// pin #28 WBO AFR "Analog Volt 10"
	engineConfiguration->afr.hwChannel = EFI_ADC_10;
}

static void customBoardDefaultConfiguration() {
	setupSdCard();
    setupCAN();
	setupVbatt();
	setupDefaultSensorInputs();
	setInjectorPins();
	setIgnitionPins();
	
    engineConfiguration->analogInputDividerCoefficient = 1.56f;

	engineConfiguration->adcVcc = 3.3f;
	engineConfiguration->is_enabled_spi_3 = false;
	

}

void setup_custom_board_overrides() {
    custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
}
