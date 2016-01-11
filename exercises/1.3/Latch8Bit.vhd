LIBRARY ieee;
USE ieee.std_logic_1164.all;
use ieee.std_logic_arith.all; 
use ieee.std_logic_unsigned.all; 
 
----------------------------------------------------------------------------
-- 8 bit latch: On rising edge of clock store data on DataIn bus to Q output
-- On reset clear all bits
----------------------------------------------------------------------------
entity Latch8Bit is
	Port (
		DataIn 		: in Std_logic_vector(7 downto 0) ;
		Enable		: in Std_logic ;
		Clk 			: in Std_logic ;
		Reset 		: in Std_logic ;
  
		Q 				: out Std_Logic_vector(7 downto 0)
	);
end ;
 
architecture bhvr of Latch8Bit is
Begin
	process(DataIn, Enable, Clk, RESET)
	Begin
		if(Reset = '0') then			-- on reset, clear all bits
			Q <= "00000000" ;
  
		elsif(rising_edge(Clk)) then
			if(Enable = '1') then
				Q <= DataIn ;
			end if ;
		end if ;
	end process ;
end ;
