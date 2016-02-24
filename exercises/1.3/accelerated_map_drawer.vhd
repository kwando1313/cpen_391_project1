library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- accelerated map drawer
entity amd is
port (
    clk: in std_logic;
    reset_n: in std_logic;
	 
    slv_addr: in std_logic_vector(15 downto 0);
	 slv_wrdata: in std_logic_vector(15 downto 0);
	 slv_write: in std_logic;
	 slv_rddata: out std_logic_vector(15 downto 0);
	 slv_read: in std_logic;
	 
	 -- why is this 32 bits? qsys didn't like 15...
    master_addr: out std_logic_vector(31 downto 0);
	 master_waitreq: in std_logic;
	 
	 master_rdata: in std_logic_vector(15 downto 0);
	 master_read: out std_logic;
	 
	 master_wrdata: out std_logic_vector(15 downto 0);
	 master_write: out std_logic
);
end amd;

architecture rtl of amd is
begin
	master_addr <= (others => '0');
	master_wrdata <= (others => '0');
	master_read <= '0';
	master_write <= '0';
	slv_rddata <= (others => '0');
end rtl;
