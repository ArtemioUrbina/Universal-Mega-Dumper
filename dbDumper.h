/*******************************************************************//**
 *  \file dbDumper.h
 *  \author René Richard
 *  \brief This program allows to read and write to various game cartridges including: Genesis, Coleco, SMS, PCE - with possibility for future expansion.
 *  
 *  Target Hardware:
 *  Teensy++2.0 with db Electronics TeensyDumper board rev >= 1.1
 *  Arduino IDE settings:
 *  Board Type  - Teensy++2.0
 *  USB Type    - Serial
 *  CPU Speed   - 16 MHz
 **********************************************************************/
 
 /*
 LICENSE
 
    This file is part of dbDumper.

    dbDumper is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    dbDumper is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with dbDumper.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef dbDumper_h
#define dbDumper_h

//#define _DEBUG_DB

  //define pins
#define DATAOUTH      PORTD		/**< PORTD used for high byte of databus output */
#define DATAOUTL      PORTC		/**< PORTD used for low byte of databus output */
#define DATAINH       PIND		/**< PIND used for high byte databus input */
#define DATAINL       PINC		/**< PINC used for low byte databus input */
#define DATAH_DDR     DDRD		/**< DDRD data direction for high byte of databus */
#define DATAL_DDR     DDRC		/**< DDRC data direction for low byte of databus */

/*******************************************************************//** 
 * \class dbDumper
 * \brief Teensy dbDumper class to read and write db Flash Carts
 **********************************************************************/
class dbDumper
{
	public:

		/*******************************************************************//**
		 * \brief eMode Type
		 * eMode is used by dbDumper to keep track of which mode is currently set
		 **********************************************************************/
		enum eMode
		{ 
			undefined, 	/**< Undefined mode */
			CV, 		/**< ColecoVision mode */
			MD, 		/**< Genesis Megadrive mode */
			TG,		 	/**< TG-16 mode */
			PC,		 	/**< PC Engine mode */
			MS			/**< Master System mode */
		};

		/*******************************************************************//**
		 * \brief Constructor
		 **********************************************************************/
		dbDumper();

		/*******************************************************************//**
		 * \brief Reset the Flash IC in the catridge
		 * \return void
		**********************************************************************/
		void resetCart();
		
		/*******************************************************************//**
		 * \brief Set the operation mode of the dbDumper
		 * \param eMode enum mode to set
		 * \return true if cartridge asserts the #CART signal
		 **********************************************************************/
		bool detectCart();
		
		/*******************************************************************//**
		 * \brief Set the operation mode of the dbDumper
		 * \param eMode enum mode to set
		 * \return void
		 **********************************************************************/
		void setMode(eMode);
		
		/*******************************************************************//**
		 * \brief Set the operation mode of the dbDumper
		 * \return eMode of currently set mode
		 **********************************************************************/
		eMode getMode() { return _mode; }

		/*******************************************************************//**
		 * \name SMS Functions
		 * This group of functions is specific to the SMS
		 **********************************************************************/
		/**@{*/
		
		/*******************************************************************//**
		 * \brief set the SMS slot register value
		 * \param uint8_t  slot number
		 * \param uint32_t address
		 * \return uint16_t address the virtual address to write to the slot
		 **********************************************************************/
		uint16_t setSMSSlotRegister(uint8_t slotNum, uint32_t address);

		/**@}*/
		
		/*******************************************************************//**
		 * \name Cartridge Flash Functions
		 * This group of functions is specific to the catridge flash
		 **********************************************************************/
		/**@{*/
		/*******************************************************************//**
		 * \brief Read the Manufacturer and Product ID in the Flash IC
		 * \return uint32_t flashID
		 **********************************************************************/
		uint32_t getFlashID();

		/*******************************************************************//**
		 * \brief Erase the entire Flash IC
		 * \param bool wait
		 * \param uint8_t chip
		 * \return uint32_t time in millis operation took to complete
		 **********************************************************************/
		uint32_t eraseChip(bool wait, uint8_t chip);
		
		/*******************************************************************//**
		 * \brief Erase a sector in the Flash IC
		 * \param uint32_t address of the sector
		 * \return void
		 **********************************************************************/
		void eraseSector(uint32_t sectorAddress);
		
		/*******************************************************************//**
		 * \brief Perform toggle bit algorithm
		 * \param uint8_t attempts
		 * \param uint8_t chip
		 * \return uint8_t success the number of times the bit did not toggle
		 **********************************************************************/
		uint8_t toggleBit(uint8_t attempts, uint8_t chip);

		/**@}*/

		/*******************************************************************//**
		 * \name Read Functions
		 * This group of functions perform various read operations
		 **********************************************************************/
		/**@{*/
		/*******************************************************************//**
		 * \brief Read a byte from a 16bit address
		 * \param address 16bit address
		 * \param external read called from outside class
		 * \return byte from cartridge
		 **********************************************************************/
		uint8_t readByte(uint16_t address, bool external);
		
		/*******************************************************************//**
		 * \brief Read a byte from a 24bit address
		 * \param address 24bit address
		 * \param external read called from outside class
		 * \return byte from cartridge
		 **********************************************************************/
		uint8_t readByte(uint32_t address, bool external);
		
		/*******************************************************************//**
		 * \brief Read a word from a 24bit address
		 * \param address 24bit address
		 * \return word from cartridge
		 **********************************************************************/
		uint16_t readWord(uint32_t address);
		
		/**@}*/
		
		/*******************************************************************//** 
		 * \name Write Functions
		 * This group of functions perform various write operations
		 **********************************************************************/
		/**@{*/
		/*******************************************************************//**
		 * \brief Write a byte to the #TIME region on genesis
		 * \param uint16_t address
		 * \param uint8_t data
		 * \return void
		 **********************************************************************/
		void writeByteTime(uint16_t address, uint8_t data);
		
		/*******************************************************************//**
		 * \brief Write a byte to a 16bit address
		 * \param address 16bit address
		 * \param data byte
		 * \return void
		 **********************************************************************/
		void writeByte(uint16_t address, uint8_t data);
		
		/*******************************************************************//**
		 * \brief Write a byte to a 24bit address
		 * \param address 24bit address
		 * \param data byte
		 * \return void
		 **********************************************************************/
		void writeByte(uint32_t address, uint8_t data);
		
		/*******************************************************************//**
		 * \brief Write a word to the #TIME region on genesis
		 * \param uint16_t address
		 * \param uint16_t data
		 * \return void
		 **********************************************************************/
		void writeWordTime(uint16_t address, uint16_t data);
		
		/*******************************************************************//**
		 * \brief Write a word to a 16bit address
		 * \param address 16bit address
		 * \param data word
		 * \return void
		 **********************************************************************/
		void writeWord(uint16_t address, uint16_t data);
		
		/*******************************************************************//**
		 * \brief Write a word to a 24bit address
		 * \param address 24bit address
		 * \param data word
		 * \return void
		 **********************************************************************/
		void writeWord(uint32_t address, uint16_t data);
		
		/**@}*/


		/*******************************************************************//** 
		 * \name Program Functions
		 * This group of functions perform various write operations
		 **********************************************************************/
		/**@{*/
		/*******************************************************************//**
		 * \brief Program a byte in the Flash IC
		 * \param address 24bit address
		 * \param data byte
		 * \param wait Wait for completion using data polling to return from function
		 * \return void
		 **********************************************************************/
		void programByte(uint32_t address, uint8_t data, bool wait);
		
		/*******************************************************************//**
		 * \brief Program a word in the Flash IC
		 * \param address 24bit address
		 * \param data word
		 * \param wait Wait for completion using data polling to return from function
		 * \return void
		 **********************************************************************/
		void programWord(uint32_t address, uint16_t data, bool wait);
	
		/**@}*/


		//pin numbers UI
		static const uint8_t nLED = 8;
		static const uint8_t nPB = 9;
		
		//Master System Slot Base Addresses
		static const uint16_t SMS_SLOT_0_ADDR = 0x0000; /**< SMS Sega Mapper slot 0 base address 0x0000 - 0x3FFF */
		static const uint16_t SMS_SLOT_1_ADDR = 0x4000; /**< SMS Sega Mapper slot 1 base address 0x4000 - 0x7FFF */
		static const uint16_t SMS_SLOT_2_ADDR = 0x8000; /**< SMS Sega Mapper slot 2 base address 0x8000 - 0xBFFF */

	private:
		uint8_t _resetPin;
		uint32_t _flashID;
		eMode _mode;
		
		//Master System Slots and slot address
		static const uint16_t SMS_CONF_REG_ADDR   = 0xFFFC; /**< SMS Sega Mapper RAM mapping and miscellaneous functions register */
		static const uint16_t SMS_SLOT_0_REG_ADDR = 0xFFFD; /**< SMS Sega Mapper slot 0 register address 0x0000 - 0x3FFF */
		static const uint16_t SMS_SLOT_1_REG_ADDR = 0xFFFE; /**< SMS Sega Mapper slot 1 register address 0x4000 - 0x7FFF */
		static const uint16_t SMS_SLOT_2_REG_ADDR = 0xFFFF; /**< SMS Sega Mapper slot 2 register address 0x8000 - 0xBFFF */

	
		inline void _latchAddress(uint16_t address);
		inline void _latchAddress(uint32_t address);

		uint8_t reverseByte(uint8_t data);

		//Genesis multichip base addresses for M29F800
		static const uint32_t GEN_CHIP_0_BASE = 0x000000;
		static const uint32_t GEN_CHIP_1_BASE = 0x100000;

		//pin numbers address control
		static const uint8_t ALE_low = 26;
		static const uint8_t ALE_high = 27;

		//globally affected pins
		static const uint8_t nRD = 25;	
		static const uint8_t nWR = 24;
		static const uint8_t nCE = 19;
		static const uint8_t nCART = 18;

		//general control pins
		static const uint8_t CTRL0 = 38;
		static const uint8_t CTRL1 = 39;
		static const uint8_t CTRL2 = 40;
		static const uint8_t CTRL3 = 41;
		static const uint8_t CTRL4 = 42;
		static const uint8_t CTRL5 = 43;
		static const uint8_t CTRL6 = 44;
		static const uint8_t CTRL7 = 45;

		//Turbografx-16 pin functions
		static const uint8_t TG_nRST = 38;

		//Coleco pin functions
		//static const uint8_t COL_nBPRES = 39;
		//static const uint8_t COL_nE000 = 38;
		//static const uint8_t COL_A16 = 38;
		//static const uint8_t COL_nC000 = 40;
		//static const uint8_t COL_A15 = 40;
		//static const uint8_t COL_nA000 = 41;
		//static const uint8_t COL_A14 = 41;
		//static const uint8_t COL_n8000 = 43;
		//static const uint8_t COL_A13 = 43;	

		//Master System pin functions
		static const uint8_t SMS_nRST = 42;
		

		//Genesis pin functions
		static const uint8_t GEN_SL1 = 38;
		static const uint8_t GEN_SR1 = 39;
		static const uint8_t GEN_nDTACK = 40;
		static const uint8_t GEN_nCAS2 = 41;
		static const uint8_t GEN_nVRES = 42;
		static const uint8_t GEN_nLWR = 43;
		static const uint8_t GEN_nUWR = 44;
		static const uint8_t GEN_nTIME = 45;
		
		//SPI pins
		static const uint8_t MISOp = 23;
		static const uint8_t MOSIp = 22;
		static const uint8_t SCKp = 21;
		static const uint8_t SCSp = 20;	
};

#endif  //dbDumper_h

