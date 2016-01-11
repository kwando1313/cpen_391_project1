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

ENTITY lights IS
	PORT (
		SW : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
		KEY : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
		CLOCK_50 : IN STD_LOGIC;
		LEDG : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
		DRAM_CLK, DRAM_CKE : OUT STD_LOGIC;
		DRAM_ADDR : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
		DRAM_BA_0, DRAM_BA_1 : BUFFER STD_LOGIC;
		DRAM_CS_N, DRAM_CAS_N, DRAM_RAS_N, DRAM_WE_N : OUT STD_LOGIC;
		DRAM_DQ : INOUT STD_LOGIC_VECTOR(15 DOWNTO 0);
		DRAM_UDQM, DRAM_LDQM : BUFFER STD_LOGIC;
		LCD_DATA    : inout std_logic_vector(7 downto 0) ; -- DATA
		LCD_ON      : out   std_logic;                     -- ON
		LCD_BLON    : out   std_logic;                     -- BLON
		LCD_EN      : out   std_logic;                     -- EN
		LCD_RS      : out   std_logic;                     -- RS
		LCD_RW      : out   std_logic;                      -- RW	
		IO_acknowledge : in    std_logic;                                  		  -- acknowledge
		IO_irq         : in    std_logic;                                 		  -- irq
		IO_address     : out   std_logic_vector(9 downto 0);                     -- address
		IO_bus_enable  : out   std_logic;                                        -- bus_enable
		IO_byte_enable : out   std_logic_vector(1 downto 0);                     -- byte_enable
		IO_rw          : out   std_logic;                                        -- rw
		IO_write_data  : out   std_logic_vector(15 downto 0);                    -- write_data
		IO_read_data   : in    std_logic_vector(15 downto 0);							  -- read_data
		UART_RXD			: in std_logic ;
		UART_TXD			: out std_logic ;
		GPS_RXD			: in std_logic ;
		GPS_TXD			: out std_logic ;
		BlueTooth_RXD	: in std_logic ;
		BlueTooth_TXD	: out std_logic
		
	);
END lights;

ARCHITECTURE Structure OF lights IS
	COMPONENT nios_system
		PORT (
			clk_clk : IN STD_LOGIC;
			reset_reset_n : IN STD_LOGIC;
			sdram_clk_clk : OUT STD_LOGIC;
			leds_export : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
			switches_export : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
			sdram_wire_addr : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
			sdram_wire_ba : BUFFER STD_LOGIC_VECTOR(1 DOWNTO 0);
			sdram_wire_cas_n : OUT STD_LOGIC;
			sdram_wire_cke : OUT STD_LOGIC;
			sdram_wire_cs_n : OUT STD_LOGIC;
			sdram_wire_dq : INOUT STD_LOGIC_VECTOR(15 DOWNTO 0);
			sdram_wire_dqm : BUFFER STD_LOGIC_VECTOR(1 DOWNTO 0);
			sdram_wire_ras_n : OUT STD_LOGIC;
			sdram_wire_we_n : OUT STD_LOGIC;
			lcd_data_DATA    : inout std_logic_vector(7 downto 0)  := (others => 'X'); -- DATA
			lcd_data_ON      : out   std_logic;                                        -- ON
			lcd_data_BLON    : out   std_logic;                                        -- BLON
			lcd_data_EN      : out   std_logic;                                        -- EN
			lcd_data_RS      : out   std_logic;                                        -- RS
			lcd_data_RW      : out   std_logic;                                         -- RW
			graphics_interface_acknowledge : in    std_logic                     := 'X';             -- acknowledge
			graphics_interface_irq         : in    std_logic                     := 'X';             -- irq
			graphics_interface_address     : out   std_logic_vector(9 downto 0);                     -- address
			graphics_interface_bus_enable  : out   std_logic;                                        -- bus_enable
			graphics_interface_byte_enable : out   std_logic_vector(1 downto 0);                     -- byte_enable
			graphics_interface_rw          : out   std_logic;                                        -- rw
			graphics_interface_write_data  : out   std_logic_vector(15 downto 0);                    -- write_data
			graphics_interface_read_data   : in    std_logic_vector(15 downto 0) := (others => 'X');  -- read_data
			rs232_RXD                      : in    std_logic                     := 'X';             -- RXD
			rs232_TXD                      : out   std_logic;                                         -- TXD
			gpschip_RXD                    : in    std_logic                     := 'X';             -- RXD
			gpschip_TXD                    : out   std_logic;                                        -- TXD
			bluetooth_RXD                  : in    std_logic                     := 'X';             -- RXD
			bluetooth_TXD                  : out   std_logic                                         -- TXD
		    	
		);
	END COMPONENT;
	
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
		clk_clk => CLOCK_50,
		reset_reset_n => KEY(0),
		sdram_clk_clk => DRAM_CLK,
		leds_export => LEDG,
		switches_export => SW,
		sdram_wire_addr => DRAM_ADDR,
		sdram_wire_ba => BA,
		sdram_wire_cas_n => DRAM_CAS_N,
		sdram_wire_cke => DRAM_CKE,
		sdram_wire_cs_n => DRAM_CS_N,
		sdram_wire_dq => DRAM_DQ,
		sdram_wire_dqm => DQM,
		sdram_wire_ras_n => DRAM_RAS_N,
		sdram_wire_we_n => DRAM_WE_N,
		lcd_data_DATA => LCD_DATA,
		lcd_data_ON => LCD_ON,
		lcd_data_BLON => LCD_BLON,
		lcd_data_EN => LCD_EN,
		lcd_data_RS => LCD_RS,
		lcd_data_RW => LCD_RW,
		graphics_interface_acknowledge => IO_acknowledge,
		graphics_interface_irq => IO_irq,
		graphics_interface_address => IO_address,
		graphics_interface_bus_enable => IO_bus_enable,
		graphics_interface_byte_enable => IO_byte_enable,
		graphics_interface_rw => IO_rw,
		graphics_interface_write_data => IO_write_data,
		graphics_interface_read_data => IO_read_data,
		rs232_RXD => UART_RXD,
		rs232_TXD => UART_TXD,
		gpschip_RXD =>	GPS_RXD,
		gpschip_TXD => GPS_TXD,
		bluetooth_RXD => BlueTooth_RXD,
		bluetooth_TXD => BlueTooth_TXD
	);
END Structure;