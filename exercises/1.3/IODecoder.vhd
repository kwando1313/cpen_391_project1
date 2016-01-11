LIBRARY ieee;
USE ieee.std_logic_1164.all;
use ieee.std_logic_arith.all; 
use ieee.std_logic_unsigned.all; 

entity IODecoder is
	Port (
		Address : in Std_logic_vector(15 downto 0) ;
		IOSelect_H : in Std_logic ;
		WE_L : in Std_Logic ;
		UDS_L : in Std_Logic ;
				
		OutputPortA_Enable : out Std_Logic;
		InputPortA_Enable : out Std_Logic;
		OutputPortB_Enable : out Std_Logic;
		InputPortB_Enable : out Std_Logic;
		OutputPortC_Enable : out Std_Logic;
		InputPortC_Enable : out Std_Logic;				
		OutputPortD_Enable : out Std_Logic;
		InputPortD_Enable : out Std_Logic;				
	   OutputPortE_Enable : out Std_Logic;
		InputPortE_Enable : out Std_Logic;				
		
		LCDCommandOrData: out Std_Logic ;
		LCDWrite : out Std_Logic;
		
		Timer1ControlReg_Enable : out Std_logic;
		Timer1DataReg_Enable : out Std_logic; 
		Timer2ControlReg_Enable : out Std_logic;
		Timer2DataReg_Enable : out Std_logic ;
		Timer3ControlReg_Enable : out Std_logic;
		Timer3DataReg_Enable : out Std_logic ;
		Timer4ControlReg_Enable : out Std_logic;
		Timer4DataReg_Enable : out Std_logic ;
		
		Timer5ControlReg_Enable : out Std_logic;
		Timer5DataReg_Enable : out Std_logic; 
		Timer6ControlReg_Enable : out Std_logic;
		Timer6DataReg_Enable : out Std_logic ;
		Timer7ControlReg_Enable : out Std_logic;
		Timer7DataReg_Enable : out Std_logic ;
		Timer8ControlReg_Enable : out Std_logic;
		Timer8DataReg_Enable : out Std_logic ;
		
		HexDisplay7and6Enable : out Std_logic ;
		HexDisplay5and4Enable : out Std_logic ;
		HexDisplay3and2Enable : out Std_logic ;
		HexDisplay1and0Enable : out Std_logic 	
	);
end ;


architecture bhvr of IODecoder is
Begin
	process(Address, IOSelect_H, WE_L, UDS_L)
	Begin
		OutputPortA_Enable <= '0' ;
		InputPortA_Enable <= '0' ;
		OutputPortB_Enable <= '0' ;
		InputPortB_Enable <= '0' ;
		OutputPortC_Enable <= '0' ;
		InputPortC_Enable <= '0' ;
		OutputPortD_Enable <= '0' ;
		InputPortD_Enable <= '0' ;
		OutputPortE_Enable <= '0' ;
		InputPortE_Enable <= '0' ;
						
		LCDCommandOrData <= '0' ;
		LCDWrite <= '0' ;
		
		Timer1DataReg_Enable <= '0' ;
		Timer1ControlReg_Enable <= '0' ;
		Timer2DataReg_Enable <= '0' ;
		Timer2ControlReg_Enable <= '0' ;
		Timer3DataReg_Enable <= '0' ;
		Timer3ControlReg_Enable <= '0' ;
		Timer4DataReg_Enable <= '0' ;
		Timer4ControlReg_Enable <= '0' ;	
		
		Timer5DataReg_Enable <= '0' ;
		Timer5ControlReg_Enable <= '0' ;
		Timer6DataReg_Enable <= '0' ;
		Timer6ControlReg_Enable <= '0' ;
		Timer7DataReg_Enable <= '0' ;
		Timer7ControlReg_Enable <= '0' ;
		Timer8DataReg_Enable <= '0' ;
		Timer8ControlReg_Enable <= '0' ;	
		
		HexDisplay7and6Enable <= '0' ;
		HexDisplay5and4Enable <= '0' ;
		HexDisplay3and2Enable <= '0' ;
		HexDisplay1and0Enable <= '0' ;
		
		
-- IO Ports located at Base Address of Hex $04000100 upwards
--	Port A = Hex 04000100 (read and write since it's a bi-directional port)
--	Port B = Hex 04000102 (read and write since it's a bi-directional port)
--	Port C = Hex 04000104 (read and write since it's a bi-directional port)
--	Port D = Hex 04000106 (read and write since it's a bi-directional port)
--	Port E = Hex 04000108 (read and write since it's a bi-directional port)

		
		if(IOSelect_H = '1') then 
			-- Port A
			if(Address = X"0100" and UDS_L = '0' ) then
				if(WE_L = '0') then
					OutputPortA_Enable <= '1' ;
				else 
					InputPortA_Enable <= '1' ;
				end if ;
			end if ;
				
			-- Port B
			if(Address = X"0102" and UDS_L = '0') then
				if(WE_L = '0') then
					OutputPortB_Enable <= '1' ;
				else 
					InputPortB_Enable <= '1' ;
				end if ;
			end if ;			
				
			-- Port C
			if(Address = X"0104" and UDS_L = '0') then
				if(WE_L = '0') then
					OutputPortC_Enable <= '1' ;
				else 
					InputPortC_Enable <= '1' ;
				end if ;
			end if ;
			
			-- Port D
			if(Address = X"0106" and UDS_L = '0') then
				if(WE_L = '0') then
					OutputPortD_Enable <= '1' ;
				else 
					InputPortD_Enable <= '1' ;
				end if ;
			end if ;
			
			-- Port E
			if(Address = X"0108" and UDS_L = '0') then
				if(WE_L = '0') then
					OutputPortE_Enable <= '1' ;
				else 
					InputPortE_Enable <= '1' ;
				end if ;
			end if ;		
			
	--	7 segment Display Port (RHS or least significant digits) = Hex 04000110
	--	7 segment Display Port (LHS or most significant digits) = Hex 04000112	
	--	7 segment Display Port (RHS or least significant digits) = Hex 04000114
	--	7 segment Display Port (LHS or most significant digits) = Hex 04000116
	
			if(Address = X"0110" and UDS_L = '0') then
				if(WE_L = '0') then
					HexDisplay1and0Enable <= '1' ;
				end if ;
			end if ;	
			
			if(Address = X"0112" and UDS_L = '0') then
				if(WE_L = '0') then
					HexDisplay3and2Enable <= '1' ;
				end if ;
			end if ;	
			
			if(Address = X"0114" and UDS_L = '0') then
				if(WE_L = '0') then
					HexDisplay5and4Enable <= '1' ;
				end if ;
			end if ;	
			
			if(Address = X"0116" and UDS_L = '0') then
				if(WE_L = '0') then
					HexDisplay7and6Enable <= '1' ;
				end if ;
			end if ;	
											
	
	--	LCD Port = Hex 04000120 for command register
	--	LCD Port = Hex 04000122 for data register
				
			if(Address = X"0120" and UDS_L = '0') then
				if(WE_L = '0') then
					LCDWrite <= '1' ;
					LCDCommandOrData <= '0' ;		-- 0 for command
				end if ;
			end if ;
			
			if(Address = X"0122" and UDS_L = '0') then
				if(WE_L = '0') then
					LCDWrite <= '1' ;
					LCDCommandOrData <= '1' ;		-- 1 for data
				end if ;
			end if ;
			
	-- decoder for the 4 Timers at base address Hex 04000130/32, 34/36, 38/3A, 3C/3E on d8-d15		
	
			if(Address = X"0130" and UDS_L = '0') then					-- Timer 1 Data Register, d8-d15
				Timer1DataReg_Enable <= '1' ;
			elsif(Address = X"0132" and UDS_L = '0') then				-- Timer 1 Control/status Register d8-d15
				Timer1ControlReg_Enable <= '1' ;
			elsif(Address = X"0134" and UDS_L = '0') then				-- Timer 2 Data Register d8-d15
				Timer2DataReg_Enable <= '1' ;
			elsif(Address = X"0136" and UDS_L = '0') then				-- Timer 2 Control/status Register d8-d15
				Timer2ControlReg_Enable <= '1' ;
			elsif(Address = X"0138" and UDS_L = '0') then				-- Timer 3 Data Register d8-d15
				Timer3DataReg_Enable <= '1' ;
			elsif(Address = X"013A" and UDS_L = '0') then				-- Timer 3 Control/status Register d8-d15
				Timer3ControlReg_Enable <= '1' ;
			elsif(Address = X"013C" and UDS_L = '0') then				-- Timer 4 Data Register d8-d15
				Timer4DataReg_Enable <= '1' ;
			elsif(Address = X"013E" and UDS_L = '0') then				-- Timer 4 Control/status Register d8-d15
				Timer4ControlReg_Enable <= '1' ;
				
-- decoder for the 2nd set of 4 Timers at base address Hex 04000140/42, 44/46, 48/4A, 4C/4E on d8-d15	
				
			elsif(Address = X"0140" and UDS_L = '0') then				-- Timer 5 Data Register, d8-d15
				Timer5DataReg_Enable <= '1' ;
			elsif(Address = X"0142" and UDS_L = '0') then				-- Timer 5 Control/status Register d8-d15
				Timer5ControlReg_Enable <= '1' ;
			elsif(Address = X"0144" and UDS_L = '0') then				-- Timer 6 Data Register d8-d15
				Timer6DataReg_Enable <= '1' ;
			elsif(Address = X"0146" and UDS_L = '0') then				-- Timer 6 Control/status Register d8-d15
				Timer6ControlReg_Enable <= '1' ;
			elsif(Address = X"0148" and UDS_L = '0') then				-- Timer 7 Data Register d8-d15
				Timer7DataReg_Enable <= '1' ;
			elsif(Address = X"014A" and UDS_L = '0') then				-- Timer 7 Control/status Register d8-d15
				Timer7ControlReg_Enable <= '1' ;
			elsif(Address = X"014C" and UDS_L = '0') then				-- Timer 8 Data Register d8-d15
				Timer8DataReg_Enable <= '1' ;
			elsif(Address = X"014E" and UDS_L = '0') then				-- Timer 8 Control/status Register d8-d15
				Timer8ControlReg_Enable <= '1' ;				
			end if ;
		end if ;
	end process ;
END ;