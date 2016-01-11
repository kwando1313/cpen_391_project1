LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;


Entity VideoRamMux is
	Port (  
	
		VGAAddress 					: in STD_LOGIC_VECTOR(17 downto 0) ;
		

		-- outputs to the Sram chip
		SRAM_ADDRESS 				: out std_logic_vector(17 downto 0) ;				-- output to address bus of video ram

		SRAM_OE_L 					: out std_logic ;											-- output enable during read and Chip select
		SRAM_CE_L 					: out std_logic ;											-- chip enable to video ram
		SRAM_WE_L 					: out std_logic ;											-- write enable to ram when CPU writes otherwise read
		SRAM_LB_L 					: out std_logic ;											-- byte enable signals for lower half of data bus note CPU only writes to one half not the other
		SRAM_UB_L 					: out std_logic ; 										-- byte enable signals for lower half of data bus note CPU only writes to one half not the other
		
		-- graphics chip signals
		GraphicsAddress			: in Std_logic_Vector(17 downto 0) ;
		GraphicsUDS_L				: in Std_logic ;
		GraphicsLDS_L				: in Std_logic ;
		GraphicsRW					: in Std_logic ;
		GraphicsCE_L				: in Std_logic ;
		GraphicsOE_L				: in Std_logic ;
		GraphicsBusy_H				: in Std_logic 
);	
end;
 
Architecture a of VideoRamMux is
begin
	process(VGAAddress, GraphicsBusy_H, GraphicsAddress, GraphicsOE_L, GraphicsCE_L, GraphicsRW, GraphicsUDS_L, GraphicsLDS_L)
	begin
	
		-- default signals assume the vga  controller is always accessing Ram

			SRAM_ADDRESS 	<= VGAAddress ;
			SRAM_OE_L 		<= '0' ;
			SRAM_CE_L 		<= '0' ;
			SRAM_WE_L 		<= '1' ;															-- read only
			SRAM_LB_L 		<= '0' ;															-- select both halves of the data bus even though only 1 half is used
			SRAM_UB_L 		<= '0' ;
	
		If(GraphicsBusy_H = '1')	then													-- graphics controller wants Ram
		-- if the graphics controller wants access to the sram
		-- then switch over the mux to present graphics controller signal to the Sram
		
			SRAM_ADDRESS 	<= GraphicsAddress ;												-- but not for horizontal scrolling
			SRAM_OE_L 		<= GraphicsOE_L ;
			SRAM_CE_L 		<= GraphicsCE_L ;
			SRAM_WE_L 		<= GraphicsRW ;
			SRAM_LB_L 		<= GraphicsLDS_L ;																-- select both halves of the data bus even though only 1 half is used
			SRAM_UB_L 		<= GraphicsUDS_L ;			
		end if ;
	end process ;
end ;
