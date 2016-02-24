library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- accelerated map drawer
entity amd is
port (
    clk: in std_logic;
    reset_n: in std_logic;
	 
    slv_addr: in std_logic_vector(15 downto 0);
	 slv_start: in std_logic;
	 slv_done: out std_logic;
	 slv_data: in std_logic_vector(15 downto 0);
	 
    master_addr: out std_logic_vector(31 downto 0);
	 
	 master_rdata: in std_logic_vector(15 downto 0);
	 master_read: out std_logic;
	 
	 master_wrdata: out std_logic_vector(15 downto 0);
	 master_write: out std_logic;
	 master_waitreq: in std_logic
);
end amd;

architecture rtl of amd is
begin
	slv_done <= '0';
	master_addr <= (others => '0');
	master_wrdata <= (others => '0');
	master_read <= '0';
	master_write <= '0';
end rtl;
