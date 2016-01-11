-- Implements a simple Nios II system for the DE2 board.
-- Inputs: SW7¡0 are parallel port inputs to the Nios II system.
-- CLOCK_50 is the system clock.
-- KEY0 is the active-low system reset.
-- Outputs: LEDG7¡0 are parallel port outputs from the Nios II system.
-- SDRAM ports correspond to the signals in Figure 2; their names are those
-- used in the DE2 User Manual.
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.std_logic_unsigned.all;

ENTITY NIOS_II_SYSTEM IS
	PORT (
		RESET : IN STD_LOGIC;
		CLOCK_50Mhz : IN STD_LOGIC;
		
		DRAM_CLK, DRAM_CKE : OUT STD_LOGIC;
		DRAM_ADDR : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
		DRAM_BA_0, DRAM_BA_1 : BUFFER STD_LOGIC;
		DRAM_CS_N, DRAM_CAS_N, DRAM_RAS_N, DRAM_WE_N : OUT STD_LOGIC;
		DRAM_DQ : INOUT STD_LOGIC_VECTOR(15 DOWNTO 0);
		DRAM_UDQM, DRAM_LDQM : BUFFER STD_LOGIC;
		
		IO_acknowledge : in    std_logic;                                  		  -- acknowledge
		IO_irq         : in    std_logic;                                 		  -- irq
		IO_address     : out   std_logic_vector(15 downto 0);                     -- address
		IO_bus_enable  : out   std_logic;                                        -- bus_enable
		IO_byte_enable : out   std_logic_vector(1 downto 0);                     -- byte_enable
		IO_rw          : out   std_logic;                                        -- rw
		IO_write_data  : out   std_logic_vector(15 downto 0);                    -- write_data
		IO_read_data   : in    std_logic_vector(15 downto 0);							  -- read_dat	
		
		STDIN        	: in    std_logic                     := 'X';             -- RXD
		STDOUT		   : out   std_logic ;                                        -- TXD	
		
		LCD_DATA		   : inout   std_logic_vector(7 downto 0);
		LCD_ON		   : out   std_logic ;
		LCD_BLON		   : out   std_logic ;
		LCD_EN		   : out   std_logic ;
		LCD_RS		   : out   std_logic ;
		LCD_RW		   : out   std_logic ;
		
		Switches   		: in    std_logic_vector(17 downto 0) := (others => 'X'); -- export
		Red_Leds		   : out   std_logic_vector(17 downto 0);                    -- export
		Green_Leds		: out   std_logic_vector(7 downto 0);                      -- export
		Push_Buttons   : in    std_logic_vector(2 downto 0)  := (others => 'X');  -- export
		Hex0_1			: out   std_logic_vector(7 downto 0) ;
		Hex2_3			: out   std_logic_vector(7 downto 0) ;
		Hex4_5			: out   std_logic_vector(7 downto 0) ;
		Hex6_7			: out   std_logic_vector(7 downto 0) 
);
END NIOS_II_SYSTEM;


	
	 
	 

ARCHITECTURE Structure OF NIOS_II_SYSTEM IS
	component nios_system is
		port (
			clk_clk                : in    std_logic                     := 'X';             -- clk
			reset_reset_n          : in    std_logic                     := 'X';             -- reset_n
			sdram_wire_addr        : out   std_logic_vector(11 downto 0);                    -- addr
			sdram_wire_ba          : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_wire_cas_n       : out   std_logic;                                        -- cas_n
			sdram_wire_cke         : out   std_logic;                                        -- cke
			sdram_wire_cs_n        : out   std_logic;                                        -- cs_n
			sdram_wire_dq          : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_wire_dqm         : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_wire_ras_n       : out   std_logic;                                        -- ras_n
			sdram_wire_we_n        : out   std_logic;                                        -- we_n
			io_acknowledge         : in    std_logic                     := 'X';             -- acknowledge
			io_irq                 : in    std_logic                     := 'X';             -- irq
			io_address             : out   std_logic_vector(15 downto 0);                    -- address
			io_bus_enable          : out   std_logic;                                        -- bus_enable
			io_byte_enable         : out   std_logic_vector(1 downto 0);                     -- byte_enable
			io_rw                  : out   std_logic;                                        -- rw
			io_write_data          : out   std_logic_vector(15 downto 0);                    -- write_data
			io_read_data           : in    std_logic_vector(15 downto 0) := (others => 'X'); -- read_data
			rs232_RXD              : in    std_logic                     := 'X';             -- RXD
			rs232_TXD              : out   std_logic;                                        -- TXD
			switches_export        : in    std_logic_vector(17 downto 0) := (others => 'X'); -- export
			red_leds_export        : out   std_logic_vector(17 downto 0);                    -- export
			green_leds_export      : out   std_logic_vector(7 downto 0);                     -- export
			lcd_display_DATA       : inout std_logic_vector(7 downto 0)  := (others => 'X'); -- DATA
			lcd_display_ON         : out   std_logic;                                        -- ON
			lcd_display_BLON       : out   std_logic;                                        -- BLON
			lcd_display_EN         : out   std_logic;                                        -- EN
			lcd_display_RS         : out   std_logic;                                        -- RS
			lcd_display_RW         : out   std_logic;                                        -- RW
			sdram_clk_clk          : out   std_logic;                                        -- clk
			push_buttons123_export : in    std_logic_vector(2 downto 0)  := (others => 'X'); -- export
			hex0_1_export          : out   std_logic_vector(7 downto 0);                     -- export
			hex2_3_export          : out   std_logic_vector(7 downto 0);                     -- export
			hex4_5_export          : out   std_logic_vector(7 downto 0);                     -- export
			hex6_7_export          : out   std_logic_vector(7 downto 0)                      -- export
		);
	end component nios_system;
	
	SIGNAL DQM : STD_LOGIC_VECTOR(1 DOWNTO 0);
	SIGNAL BA : STD_LOGIC_VECTOR(1 DOWNTO 0);

BEGIN
	DRAM_BA_0 <= BA(0);
	DRAM_BA_1 <= BA(1);
	DRAM_UDQM <= DQM(1);
	DRAM_LDQM <= DQM(0);
	
	-- Instantiate the Nios II system entity generated by the Qsys tool.
	NiosII: nios_system
	PORT MAP (
		clk_clk => CLOCK_50Mhz,
		reset_reset_n => RESET,
		
		sdram_clk_clk => DRAM_CLK,
		sdram_wire_addr => DRAM_ADDR,
		sdram_wire_ba => BA,
		sdram_wire_cas_n => DRAM_CAS_N,
		sdram_wire_cke => DRAM_CKE,
		sdram_wire_cs_n => DRAM_CS_N,
		sdram_wire_dq => DRAM_DQ,
		sdram_wire_dqm => DQM,
		sdram_wire_ras_n => DRAM_RAS_N,
		sdram_wire_we_n => DRAM_WE_N,
		
		io_acknowledge => IO_acknowledge,
		io_irq => IO_irq,
		io_address => IO_address,
		io_bus_enable => IO_bus_enable,
		io_byte_enable => IO_byte_enable,
		io_rw => IO_rw,
		io_write_data => IO_write_data,
		io_read_data => IO_read_data,
		
		rs232_RXD => STDIN,
		rs232_TXD => STDOUT,
		
		lcd_display_DATA => LCD_DATA,
		lcd_display_ON => LCD_ON,
		lcd_display_BLON => LCD_BLON,
		lcd_display_EN => LCD_EN,
		lcd_display_RS => LCD_RS,
		lcd_display_RW => LCD_RW,
		
		switches_export => Switches,   
		red_leds_export => Red_Leds,  
		green_leds_export => Green_Leds,
		push_buttons123_export => Push_Buttons,
		
		hex0_1_export => Hex0_1,
		hex2_3_export => Hex2_3,
		hex4_5_export => Hex4_5,
		hex6_7_export => Hex6_7
	);
END Structure;