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
			coleco, 	/**< ColecoVision mode */
			genesis, 	/**< Genesis Megadrive mode */
			pcengine 	/**< PC Engine TG-16 mode */
		};

		/*******************************************************************//**
		 * \brief Constructor
		 **********************************************************************/
		dbDumper();

		/*******************************************************************//**
		 * \brief Reset the Flash IC in the catridge
		**********************************************************************/
		void resetCart();
		
		/*******************************************************************//**
		 * \brief Set the operation mode of the dbDumper
		 * 
		 * \param eMode enum mode to set
		 **********************************************************************/
		bool detectCart();
		
		/*******************************************************************//**
		 * \brief Set the operation mode of the dbDumper
		 * 
		 * \param eMode enum mode to set
		 **********************************************************************/
		void setMode(eMode);
		
		/*******************************************************************//**
		 * \brief Set the operation mode of the dbDumper
		 * 
		 * \param eMode enum mode to set
		 */
		eMode getMode() { return _mode; }

		/*******************************************************************//**
		 * \brief Read the Manufacturer and Product ID in the Flash IC
		 **********************************************************************/
		uint16_t getFlashID();


		/*******************************************************************//**
		 * \name Read Functions
		 * This group of functions perform various read operations
		 **********************************************************************/
		/**@{*/
		
		/*******************************************************************//**
		 * \brief Read a byte from a 16bit address
		 * 
		 * \param address 16bit address
		 **********************************************************************/
		uint8_t readByte(uint16_t address);
		
		/*******************************************************************//**
		 * \brief Read a byte from a 24bit address
		 * 
		 * \param address 24bit address
		 **********************************************************************/
		uint8_t readByte(uint32_t address);
		
		/*******************************************************************//**
		 * \brief Read a byte block from a 16 bit address
		 * 
		 * \param address 16bit address
		 * \param buf a pointer to store the byte block
		 * \param blockSize number of bytes to read from the block
		 **********************************************************************/
		void readByteBlock(uint16_t address, uint8_t * buf, uint16_t blockSize);
		
		/*******************************************************************//**
		 * \brief Read a byte block from a 24 bit address
		 * 
		 * \param address 24bit address
		 * \param buf a pointer to store the byte block
		 * \param blockSize number of bytes to read from the block
		 **********************************************************************/
		void readByteBlock(uint32_t address, uint8_t * buf, uint16_t blockSize);
		
		/*******************************************************************//**
		 * \brief Read a word from a 16bit address
		 * 
		 * \param address 16bit address
		 **********************************************************************/
		uint16_t readWord(uint16_t address);
		
		/*******************************************************************//**
		 * \brief Read a word from a 24bit address
		 * 
		 * \param address 24bit address
		 **********************************************************************/
		uint16_t readWord(uint32_t address);
		
		/*******************************************************************//**
		 * \brief Read a word block from a 16 bit address
		 * 
		 * \param address 16bit address
		 * \param buf a pointer to store the byte block
		 * \param blockSize number of bytes to read from the block
		 **********************************************************************/
		void readWordBlock(uint32_t address, uint8_t * buf, uint16_t blockSize);
		
		/*******************************************************************//**
		 * \brief Read a word block from a 24 bit address
		 * 
		 * \param address 24bit address
		 * \param buf a pointer to store the byte block
		 * \param blockSize number of bytes to read from the block
		 **********************************************************************/
		void readWordBlock(uint32_t address, uint8_t * buf, uint16_t blockSize);
		
		/**@}*/
		
		/*******************************************************************//** 
		 * \name Write Functions
		 * This group of functions perform various write operations
		 **********************************************************************/
		/**@{*/
		
		/*******************************************************************//**
		 * \brief Write a byte to a 16bit address
		 * 
		 * \param address 16bit address
		 * \param data byte
		 **********************************************************************/
		void writeByte(uint16_t address, uint8_t data);
		
		/*******************************************************************//**
		 * \brief Write a byte to a 24bit address
		 * 
		 * \param address 24bit address
		 * \param data byte
		 **********************************************************************/
		void writeByte(uint32_t address, uint8_t data);
		
		/*******************************************************************//**
		 * \brief Write a word to a 16bit address
		 * 
		 * \param address 16bit address
		 * \param data word
		 **********************************************************************/
		void writeWord(uint16_t address, uint16_t data);
		
		/*******************************************************************//**
		 * \brief Write a word to a 24bit address
		 * 
		 * \param address 24bit address
		 * \param data word
		 **********************************************************************/
		void writeWord(uint32_t address, uint16_t data);
		
		/**@}*/
		
		//erase
		void eraseChip(void);
		void eraseSector(uint16_t sectorAddress);
		uint8_t toggleBit(uint8_t attempts);
		
		//program
		void programByte(uint16_t address, uint8_t data, bool wait);
		void programByte(uint32_t address, uint8_t data, bool wait);
		void programWord(uint32_t address, uint16_t data, bool wait);
		
		//pin numbers UI
		static const uint8_t nLED = 8;
		static const uint8_t nPB = 9;

	private:
		uint8_t _resetPin;
		uint16_t _flashID;
		eMode _mode;
	
		inline void _latchAddress(uint16_t address);
		inline void _latchAddress(uint32_t address);
		
		void _colSoftwareIDEntry();
		void _colSoftwareIDExit();
		void _colAddrRangeSet(uint16_t address);
		void _colPinMode();

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

		//Coleco pin functions
		static const uint8_t COL_nBPRES = 39;
		static const uint8_t COL_nE000 = 38;
		static const uint8_t COL_A16 = 38;
		static const uint8_t COL_nC000 = 40;
		static const uint8_t COL_A15 = 40;
		static const uint8_t COL_nA000 = 41;
		static const uint8_t COL_A14 = 41;
		static const uint8_t COL_n8000 = 43;
		static const uint8_t COL_A13 = 43;	

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

