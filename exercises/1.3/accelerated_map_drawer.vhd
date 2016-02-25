library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- accelerated map drawer
entity amd is
port (
    clk: in std_logic;
    reset_n: in std_logic;

    slv_addr: in std_logic_vector(1 downto 0);
	 slv_wrdata	: in std_logic_vector(31 downto 0);
	 slv_write: in std_logic;
	 slv_rddata	: out std_logic_vector(31 downto 0);
	 slv_read: in std_logic;

	 -- why is this 32 bits? qsys didn't like 15...
	 -- note: what if memory addr passed in is on on_chip_memory, rather than the sdram?
    master_addr: out std_logic_vector(31 downto 0);
	 master_waitreq: in std_logic;

	 master_rddata	: in std_logic_vector(31 downto 0);
	 master_read: out std_logic;

	 master_wrdata	: out std_logic_vector(31 downto 0);
	 master_write: out std_logic
);
end amd;

architecture rtl of amd is
	signal data : std_logic_vector(31 downto 0) := (others => '0');
begin
	master_addr <= (others => '0');
	master_wrdata	 <= (others => '0');
	master_read <= '0';
	master_write <= '0';

	process(reset_n, clk)
	begin
		if (reset_n = '0') then
				data <= (others => '0');
		elsif (rising_edge(clk)) then
			if (slv_write = '1') then
				data <= slv_wrdata;
			end if;
		end if; 
	end process;

	process(clk)
	begin
		if (rising_edge(clk)) then
			if (slv_read = '1') then
				slv_rddata <= x"ffffff" & data(7 downto 0);
			end if;
		end if;
	end process;
	
--	    slv_addr: in std_logic_vector(15 downto 0);
--	 slv_wrdata: in std_logic_vector(15 downto 0);
--	 slv_write: in std_logic;
--	 slv_rddata: out std_logic_vector(15 downto 0);
	-- slv_read: in std_logic;
end rtl;
