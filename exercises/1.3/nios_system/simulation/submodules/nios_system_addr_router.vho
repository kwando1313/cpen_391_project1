--IP Functional Simulation Model
--VERSION_BEGIN 13.0 cbx_mgl 2013:06:12:18:04:42:SJ cbx_simgen 2013:06:12:18:03:40:SJ  VERSION_END


-- Copyright (C) 1991-2013 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- You may only use these simulation model output files for simulation
-- purposes and expressly not for synthesis or any other purposes (in which
-- event Altera disclaims all warranties of any kind).


--synopsys translate_off

--synthesis_resources = mux21 31 
 LIBRARY ieee;
 USE ieee.std_logic_1164.all;

 ENTITY  nios_system_addr_router IS 
	 PORT 
	 ( 
		 clk	:	IN  STD_LOGIC;
		 reset	:	IN  STD_LOGIC;
		 sink_data	:	IN  STD_LOGIC_VECTOR (99 DOWNTO 0);
		 sink_endofpacket	:	IN  STD_LOGIC;
		 sink_ready	:	OUT  STD_LOGIC;
		 sink_startofpacket	:	IN  STD_LOGIC;
		 sink_valid	:	IN  STD_LOGIC;
		 src_channel	:	OUT  STD_LOGIC_VECTOR (7 DOWNTO 0);
		 src_data	:	OUT  STD_LOGIC_VECTOR (99 DOWNTO 0);
		 src_endofpacket	:	OUT  STD_LOGIC;
		 src_ready	:	IN  STD_LOGIC;
		 src_startofpacket	:	OUT  STD_LOGIC;
		 src_valid	:	OUT  STD_LOGIC
	 ); 
 END nios_system_addr_router;

 ARCHITECTURE RTL OF nios_system_addr_router IS

	 ATTRIBUTE synthesis_clearbox : natural;
	 ATTRIBUTE synthesis_clearbox OF RTL : ARCHITECTURE IS 1;
	 SIGNAL	wire_nios_system_addr_router_src_channel_20m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_21m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_29m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_32m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_33m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_41m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_42m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_44m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_45m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_53m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_54m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_56m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_57m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_58m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_65m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_66m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_68m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_69m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_channel_70m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_data_24m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_data_35m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_data_36m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_data_47m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_data_48m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_data_49m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_data_59m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_data_60m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_data_61m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_data_71m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_data_72m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_src_data_73m_dataout	:	STD_LOGIC;
	 SIGNAL  wire_w_lg_w_sink_data_range120w367w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w1w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w2w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w_sink_data_range123w337w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  s_wire_nios_system_addr_router_src_channel_0_330_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_nios_system_addr_router_src_channel_1_358_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_nios_system_addr_router_src_channel_2_386_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_nios_system_addr_router_src_channel_3_414_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_nios_system_addr_router_src_channel_4_442_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_nios_system_addr_router_src_channel_5_470_dataout :	STD_LOGIC;
	 SIGNAL  wire_w_sink_data_range120w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_sink_data_range123w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
 BEGIN

	wire_w_lg_w_sink_data_range120w367w(0) <= wire_w_sink_data_range120w(0) AND wire_w_lg_w_sink_data_range123w337w(0);
	wire_w1w(0) <= NOT s_wire_nios_system_addr_router_src_channel_0_330_dataout;
	wire_w2w(0) <= NOT s_wire_nios_system_addr_router_src_channel_2_386_dataout;
	wire_w_lg_w_sink_data_range123w337w(0) <= NOT wire_w_sink_data_range123w(0);
	s_wire_nios_system_addr_router_src_channel_0_330_dataout <= (((((((((((((((NOT sink_data(48)) AND (NOT sink_data(49))) AND (NOT sink_data(50))) AND (NOT sink_data(51))) AND (NOT sink_data(52))) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND (NOT sink_data(56))) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND (NOT sink_data(60))) AND (NOT sink_data(61))) AND (NOT sink_data(62)));
	s_wire_nios_system_addr_router_src_channel_1_358_dataout <= ((((((((((((((((((((((((NOT sink_data(39)) AND wire_w_lg_w_sink_data_range123w337w(0)) AND sink_data(41)) AND (NOT sink_data(42))) AND (NOT sink_data(43))) AND (NOT sink_data(44))) AND (NOT sink_data(45))) AND (NOT sink_data(46))) AND (NOT sink_data(47))) AND sink_data(48)) AND (NOT sink_data(49))) AND (NOT sink_data(50))) AND (NOT sink_data(51))) AND (NOT sink_data(52))) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND (NOT sink_data(56))) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND (NOT sink_data(60))) AND (NOT sink_data(61))) AND (NOT sink_data(62)));
	s_wire_nios_system_addr_router_src_channel_2_386_dataout <= ((((((((((((((((((((((wire_w_lg_w_sink_data_range120w367w(0) AND sink_data(41)) AND (NOT sink_data(42))) AND (NOT sink_data(43))) AND (NOT sink_data(44))) AND (NOT sink_data(45))) AND (NOT sink_data(46))) AND (NOT sink_data(47))) AND sink_data(48)) AND (NOT sink_data(49))) AND (NOT sink_data(50))) AND (NOT sink_data(51))) AND (NOT sink_data(52))) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND (NOT sink_data(56))) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND (NOT sink_data(60))) AND (NOT sink_data(61))) AND (NOT sink_data(62)));
	s_wire_nios_system_addr_router_src_channel_3_414_dataout <= (((((((((((((((sink_data(47) AND sink_data(48)) AND (NOT sink_data(49))) AND (NOT sink_data(50))) AND (NOT sink_data(51))) AND (NOT sink_data(52))) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND (NOT sink_data(56))) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND (NOT sink_data(60))) AND (NOT sink_data(61))) AND (NOT sink_data(62)));
	s_wire_nios_system_addr_router_src_channel_4_442_dataout <= ((((NOT sink_data(59)) AND sink_data(60)) AND (NOT sink_data(61))) AND (NOT sink_data(62)));
	s_wire_nios_system_addr_router_src_channel_5_470_dataout <= (((((((((((NOT sink_data(52)) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND (NOT sink_data(56))) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND (NOT sink_data(60))) AND (NOT sink_data(61))) AND sink_data(62));
	sink_ready <= src_ready;
	src_channel <= ( "0" & "0" & wire_nios_system_addr_router_src_channel_65m_dataout & wire_nios_system_addr_router_src_channel_66m_dataout & s_wire_nios_system_addr_router_src_channel_5_470_dataout & wire_nios_system_addr_router_src_channel_68m_dataout & wire_nios_system_addr_router_src_channel_69m_dataout & wire_nios_system_addr_router_src_channel_70m_dataout);
	src_data <= ( sink_data(99 DOWNTO 90) & wire_nios_system_addr_router_src_data_71m_dataout & wire_nios_system_addr_router_src_data_72m_dataout & wire_nios_system_addr_router_src_data_73m_dataout & sink_data(86 DOWNTO 0));
	src_endofpacket <= sink_endofpacket;
	src_startofpacket <= sink_startofpacket;
	src_valid <= sink_valid;
	wire_w_sink_data_range120w(0) <= sink_data(39);
	wire_w_sink_data_range123w(0) <= sink_data(40);
	wire_nios_system_addr_router_src_channel_20m_dataout <= wire_w1w(0) AND NOT(s_wire_nios_system_addr_router_src_channel_1_358_dataout);
	wire_nios_system_addr_router_src_channel_21m_dataout <= s_wire_nios_system_addr_router_src_channel_0_330_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_1_358_dataout);
	wire_nios_system_addr_router_src_channel_29m_dataout <= s_wire_nios_system_addr_router_src_channel_1_358_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_2_386_dataout);
	wire_nios_system_addr_router_src_channel_32m_dataout <= wire_nios_system_addr_router_src_channel_20m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_2_386_dataout);
	wire_nios_system_addr_router_src_channel_33m_dataout <= wire_nios_system_addr_router_src_channel_21m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_2_386_dataout);
	wire_nios_system_addr_router_src_channel_41m_dataout <= wire_nios_system_addr_router_src_channel_29m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_3_414_dataout);
	wire_nios_system_addr_router_src_channel_42m_dataout <= s_wire_nios_system_addr_router_src_channel_2_386_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_3_414_dataout);
	wire_nios_system_addr_router_src_channel_44m_dataout <= wire_nios_system_addr_router_src_channel_32m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_3_414_dataout);
	wire_nios_system_addr_router_src_channel_45m_dataout <= wire_nios_system_addr_router_src_channel_33m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_3_414_dataout);
	wire_nios_system_addr_router_src_channel_53m_dataout <= wire_nios_system_addr_router_src_channel_41m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_4_442_dataout);
	wire_nios_system_addr_router_src_channel_54m_dataout <= wire_nios_system_addr_router_src_channel_42m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_4_442_dataout);
	wire_nios_system_addr_router_src_channel_56m_dataout <= wire_nios_system_addr_router_src_channel_44m_dataout OR s_wire_nios_system_addr_router_src_channel_4_442_dataout;
	wire_nios_system_addr_router_src_channel_57m_dataout <= wire_nios_system_addr_router_src_channel_45m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_4_442_dataout);
	wire_nios_system_addr_router_src_channel_58m_dataout <= s_wire_nios_system_addr_router_src_channel_3_414_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_4_442_dataout);
	wire_nios_system_addr_router_src_channel_65m_dataout <= wire_nios_system_addr_router_src_channel_53m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_5_470_dataout);
	wire_nios_system_addr_router_src_channel_66m_dataout <= wire_nios_system_addr_router_src_channel_54m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_5_470_dataout);
	wire_nios_system_addr_router_src_channel_68m_dataout <= wire_nios_system_addr_router_src_channel_56m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_5_470_dataout);
	wire_nios_system_addr_router_src_channel_69m_dataout <= wire_nios_system_addr_router_src_channel_57m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_5_470_dataout);
	wire_nios_system_addr_router_src_channel_70m_dataout <= wire_nios_system_addr_router_src_channel_58m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_5_470_dataout);
	wire_nios_system_addr_router_src_data_24m_dataout <= s_wire_nios_system_addr_router_src_channel_0_330_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_1_358_dataout);
	wire_nios_system_addr_router_src_data_35m_dataout <= s_wire_nios_system_addr_router_src_channel_1_358_dataout OR s_wire_nios_system_addr_router_src_channel_2_386_dataout;
	wire_nios_system_addr_router_src_data_36m_dataout <= wire_nios_system_addr_router_src_data_24m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_2_386_dataout);
	wire_nios_system_addr_router_src_data_47m_dataout <= wire_nios_system_addr_router_src_data_35m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_3_414_dataout);
	wire_nios_system_addr_router_src_data_48m_dataout <= wire_nios_system_addr_router_src_data_36m_dataout OR s_wire_nios_system_addr_router_src_channel_3_414_dataout;
	wire_nios_system_addr_router_src_data_49m_dataout <= wire_w2w(0) AND NOT(s_wire_nios_system_addr_router_src_channel_3_414_dataout);
	wire_nios_system_addr_router_src_data_59m_dataout <= wire_nios_system_addr_router_src_data_47m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_4_442_dataout);
	wire_nios_system_addr_router_src_data_60m_dataout <= wire_nios_system_addr_router_src_data_48m_dataout AND NOT(s_wire_nios_system_addr_router_src_channel_4_442_dataout);
	wire_nios_system_addr_router_src_data_61m_dataout <= wire_nios_system_addr_router_src_data_49m_dataout OR s_wire_nios_system_addr_router_src_channel_4_442_dataout;
	wire_nios_system_addr_router_src_data_71m_dataout <= wire_nios_system_addr_router_src_data_59m_dataout OR s_wire_nios_system_addr_router_src_channel_5_470_dataout;
	wire_nios_system_addr_router_src_data_72m_dataout <= wire_nios_system_addr_router_src_data_60m_dataout OR s_wire_nios_system_addr_router_src_channel_5_470_dataout;
	wire_nios_system_addr_router_src_data_73m_dataout <= wire_nios_system_addr_router_src_data_61m_dataout OR s_wire_nios_system_addr_router_src_channel_5_470_dataout;

 END RTL; --nios_system_addr_router
--synopsys translate_on
--VALID FILE
