LIBRARY ieee;
USE ieee.Std_Logic_1164.all;
use ieee.Std_Logic_arith.all; 
use ieee.Std_Logic_signed.all; 

-------------------------------------------------------------------------------------------------------------------------------------- 
entity EndianSwapper is
 Port ( 
		Enable		: in std_logic ;
 		DataIn		: in Std_Logic_Vector(15 downto 0);				-- 16 bit data bus in from Sram (16 bit represents 2 pixels worth of data)
		DataOut		: out Std_Logic_Vector(15 downto 0) 
	);
end;
 
architecture bhvr of EndianSwapper is
begin
	process(Enable, DataIn)
	begin
		if(Enable = '1')	then
			DataOut(15 downto 8) <= DataIn(7 downto 0) ;
			DataOut(7 downto 0) <= DataIn(15 downto 8) ;
		else
			DataOut <= "ZZZZZZZZZZZZZZZZ" ;
		end if ;
	end process ;
end;
