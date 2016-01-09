LIBRARY ieee;
USE ieee.std_logic_1164.all;
use ieee.std_logic_arith.all; 
use ieee.std_logic_unsigned.all; 

entity M68xxIODecoder is
	Port (
		Address 						: in Std_logic_vector(15 downto 0) ;
		IOSelect_H 					: in Std_logic ;
		ByteSelect_L				: in Std_Logic ;
		
		RS232_Port_Enable 		: out std_logic;
		RS232_Baud_Enable 		: out std_logic;
		GPS_Port_Enable 			: out std_logic;
		GPS_Baud_Enable 			: out std_logic;
		Bluetooth_Port_Enable 	: out std_logic;
		Bluetooth_Baud_Enable 	: out std_logic;
		TouchScreen_Port_Enable : out std_logic;
		TouchScreen_Baud_Enable : out std_logic
	);
end ;


architecture bhvr of M68xxIODecoder is
Begin
	process(Address, IOSelect_H, ByteSelect_L)
	Begin
		
-- these are the default values that will be output to 6850 ACIA and Baud rate generator chip enables 
-- the default value is low i.e. disabled. Default values are necessary to avoid inferring latches in VHDL
-- remember in VHDL unless an output is assigned a value through each and every path through a process, a 
-- latch will be created to remember a previous value - we don't want memory in our address decoder, 
-- we only want combinational logic
-- Therefore the easiest way to do this is to make sure each output is assigned a value at the START of a process, 
-- then, it doesn't matter what VHDL if-else logic comes next, the output will always have ben assigned a value 
-- so no latches will be inferred
-- Of course we can override the default output ant any time we like within our if-else VHDL statements
-- we must override them below when the CPU outputs an address for the 6850 or baud rate generator 
	
		RS232_Port_Enable 			<= '0' ;
		RS232_Baud_Enable	 			<= '0' ;
		
		GPS_Port_Enable				<= '0' ;
		GPS_Baud_Enable 				<= '0' ;
		
		Bluetooth_Port_Enable 		<= '0' ;
		Bluetooth_Baud_Enable	 	<= '0' ;
		
		TouchScreen_Port_Enable 	<= '0' ;
		TouchScreen_Baud_Enable 	<= '0' ;
	

-- IOSelect_H comes from the Avalon to External Bridge (see tutorial 1.8a) and is driven to logic 1 whenever the 
-- CPU outputs an  address in the range A31:A0 = hex [8400_0000] to [8400_FFFF]. -- that is, IOSelect_H is active 
-- high for all addresses in the range [8400_XXXX]. All we have to do for is decode the XXXX i.e. the lowest 16 
-- address lines (A15:A0) to provide various chip enables.
-- Both the 6850 ACIA and the baud rate generates are connected to the lower half of the data bus (D7:D0) and 
-- thus occupy EVEN valued addresses in the CPU address space e.g. 8400_0000, 8400_0002 etc.
-- ByteSelect_L is asserted for an even byte transfer of D7-D0

-- example decoder for the 1st 6850 chip (RS232 Port) 
-- 2 internal registers at locations 0x8400 0200 and 0x8400 0202 so that they occupy same half of data bus 
-- on D7-D0. Enabled when ByteSelect_L = 0 (i.e. activated when the data is being transferred over data bus
-- decoder for the Baud Rate generator at 0x8400_0204 on D7-D0 and ByteSelect_L = 0

		if(IOSelect_H = '1') then		-- if Avalon to External Bridge being accessed by CPU

-- if address in range hex 8400_020X i.e. 8400_0200 - 8400_020F  i.e. 16 bytes in total even though not all used

			if((Address(15 downto 4) = X"020") and ByteSelect_L = '0') then	
	
-- if address is hex 8400_0200 or 8400_0202

			   if((Address(3 downto 0) = X"0") OR (Address(3 downto 0) = X"2")) then	
					RS232_Port_Enable <= '1' ;		-- enable the ACIA device
			   end if ;
				
-- if address is hex 8400_0204 enable baud rate generator 

				if(Address(3 downto 0) = X"4") then				
					RS232_Baud_Enable <= '1' ;
				end if ;
			end if ;
		end if ;		
		
--------------------------------------------------------------------------------------------------------------------------------		
-- add other decoders for 3 more 6850 ACIA and 3 more baud rate generators, 
-- one for the GPS, Bluetooth and Touch screen devices
-- Make sure IOSelect_H is logic 1 and ByteSelect_L = logic 0, then decode the address and produce 
-- and produce the relevant enable output
-- to override the default output set above
--------------------------------------------------------------------------------------------------------------------------------

-- decoder for the 2nd 6850 chip (GPS)- 4 internal registers at addresses 0x8400_0210 and 0x8400_0212 so that 
-- Status Register (read only) and Command Register (write only) are at location 0x8400_210
-- Transmit Data Register (write only) and Received Data Register (read only) are at location 0x8400_0212
-- Each byte wide register is connected to the lower half of the 16 bit data bus coming from the bridge
-- i.e. data bus on D7-D0. The signal ByteSelect_L will be '0' when data is being transferred over the bridge data lines D7-D0 
-- so that they occupy same half of data bus on D7-D0 and ByteSelect_L = 0
--
-- decoder for the Baud Rate generator. 1 internal (write only) register at address 0x8400_0214 on D7-D0 
-- and ByteSelect_L = 0
	
-- your VHDL code for 2nd serial port and baud rate generator decoder goes here
	
-- decoder for the 3rd 6850 chip (Bluetooth)- 4 internal registers at addresses 0x8400_0220 and 0x8400_0222
-- Status Register (read only) and Command Register (write only) are at location 0x8400_220
-- Transmit Data Register (write only) and Received Data Register (read only) are at location 0x8400_0222
-- Each byte wide register is connected to the lower half of the 16 bit data bus coming from the bridge
-- i.e. data bus on D7-D0. The signal ByteSelect_L will be '0' when data is being transferred over the bridge data lines D7-D0 
-- so that they occupy same half of data bus on D7-D0 and ByteSelect_L = 0
--
-- decoder for the Baud Rate generator. 1 internal (write only) register at address 0x8400_0224 on D7-D0 
-- and ByteSelect_L = 0

-- your VHDL code for 3rd serial port and baud rate generator goes here		
		
-- decoder for the 4th 6850 chip (Touch Screen)- 4 internal byte wide registers at addresses 0x8400_0230 and 0x8400_0232
-- Status Register (read only) and Command Register (write only) are at location 0x8400_230
-- Transmit Data Register (write only) and Received Data Register (read only) are at location 0x8400_0232
-- Each byte wide register is connected to the lower half of the 16 bit data bus coming from the bridge
-- i.e. data bus on D7-D0. The signal ByteSelect_L will be '0' when data is being transferred over the bridge data lines D7-D0
-- 
-- decoder for the Baud Rate generator. 1 internal (write only) register at address 0x8400_0234 data on D7-D0 
-- and ByteSelect_L = 0
		
-- your VHDL code for 4th serial port and baud rate generator goes here

	end process;
END ;
