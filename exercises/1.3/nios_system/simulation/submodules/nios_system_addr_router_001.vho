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

--synthesis_resources = mux21 52 
 LIBRARY ieee;
 USE ieee.std_logic_1164.all;

 ENTITY  nios_system_addr_router_001 IS 
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
 END nios_system_addr_router_001;

 ARCHITECTURE RTL OF nios_system_addr_router_001 IS

	 ATTRIBUTE synthesis_clearbox : natural;
	 ATTRIBUTE synthesis_clearbox OF RTL : ARCHITECTURE IS 1;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_20m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_21m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_28m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_32m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_33m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_39m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_40m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_44m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_45m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_51m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_52m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_53m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_56m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_57m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_63m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_64m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_65m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_66m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_68m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_69m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_75m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_76m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_77m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_78m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_80m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_81m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_82m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_87m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_88m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_89m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_90m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_92m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_93m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_channel_94m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_24m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_36m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_37m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_47m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_48m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_49m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_59m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_60m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_61m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_71m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_72m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_73m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_83m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_84m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_85m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_95m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_96m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_nios_system_addr_router_001_src_data_97m_dataout	:	STD_LOGIC;
	 SIGNAL  wire_w_lg_w_sink_data_range120w411w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w1w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w2w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w_sink_data_range123w335w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  s_wire_nios_system_addr_router_001_src_channel_0_354_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_nios_system_addr_router_001_src_channel_1_382_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_nios_system_addr_router_001_src_channel_2_410_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_nios_system_addr_router_001_src_channel_3_438_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_nios_system_addr_router_001_src_channel_4_466_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_nios_system_addr_router_001_src_channel_5_494_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_nios_system_addr_router_001_src_channel_6_522_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_nios_system_addr_router_001_src_channel_7_550_dataout :	STD_LOGIC;
	 SIGNAL  wire_w_sink_data_range120w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_sink_data_range123w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
 BEGIN

	wire_w_lg_w_sink_data_range120w411w(0) <= wire_w_sink_data_range120w(0) AND wire_w_lg_w_sink_data_range123w335w(0);
	wire_w1w(0) <= NOT s_wire_nios_system_addr_router_001_src_channel_0_354_dataout;
	wire_w2w(0) <= NOT s_wire_nios_system_addr_router_001_src_channel_1_382_dataout;
	wire_w_lg_w_sink_data_range123w335w(0) <= NOT wire_w_sink_data_range123w(0);
	s_wire_nios_system_addr_router_001_src_channel_0_354_dataout <= (((((((((((((((NOT sink_data(48)) AND (NOT sink_data(49))) AND (NOT sink_data(50))) AND (NOT sink_data(51))) AND (NOT sink_data(52))) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND (NOT sink_data(56))) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND (NOT sink_data(60))) AND (NOT sink_data(61))) AND (NOT sink_data(62)));
	s_wire_nios_system_addr_router_001_src_channel_1_382_dataout <= ((((((((((((((((((((((((NOT sink_data(39)) AND wire_w_lg_w_sink_data_range123w335w(0)) AND (NOT sink_data(41))) AND (NOT sink_data(42))) AND (NOT sink_data(43))) AND (NOT sink_data(44))) AND (NOT sink_data(45))) AND (NOT sink_data(46))) AND (NOT sink_data(47))) AND sink_data(48)) AND (NOT sink_data(49))) AND (NOT sink_data(50))) AND (NOT sink_data(51))) AND (NOT sink_data(52))) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND (NOT sink_data(56))) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND (NOT sink_data(60))) AND (NOT sink_data(61))) AND (NOT sink_data(62)));
	s_wire_nios_system_addr_router_001_src_channel_2_410_dataout <= (((((((((((((((((((((((sink_data(39) AND sink_data(40)) AND (NOT sink_data(41))) AND (NOT sink_data(42))) AND (NOT sink_data(43))) AND (NOT sink_data(44))) AND (NOT sink_data(45))) AND (NOT sink_data(46))) AND (NOT sink_data(47))) AND sink_data(48)) AND (NOT sink_data(49))) AND (NOT sink_data(50))) AND (NOT sink_data(51))) AND (NOT sink_data(52))) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND (NOT sink_data(56))) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND (NOT sink_data(60))) AND (NOT sink_data(61))) AND (NOT sink_data(62)));
	s_wire_nios_system_addr_router_001_src_channel_3_438_dataout <= ((((((((((((((((((((((((NOT sink_data(39)) AND wire_w_lg_w_sink_data_range123w335w(0)) AND sink_data(41)) AND (NOT sink_data(42))) AND (NOT sink_data(43))) AND (NOT sink_data(44))) AND (NOT sink_data(45))) AND (NOT sink_data(46))) AND (NOT sink_data(47))) AND sink_data(48)) AND (NOT sink_data(49))) AND (NOT sink_data(50))) AND (NOT sink_data(51))) AND (NOT sink_data(52))) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND (NOT sink_data(56))) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND (NOT sink_data(60))) AND (NOT sink_data(61))) AND (NOT sink_data(62)));
	s_wire_nios_system_addr_router_001_src_channel_4_466_dataout <= ((((((((((((((((((((((wire_w_lg_w_sink_data_range120w411w(0) AND sink_data(41)) AND (NOT sink_data(42))) AND (NOT sink_data(43))) AND (NOT sink_data(44))) AND (NOT sink_data(45))) AND (NOT sink_data(46))) AND (NOT sink_data(47))) AND sink_data(48)) AND (NOT sink_data(49))) AND (NOT sink_data(50))) AND (NOT sink_data(51))) AND (NOT sink_data(52))) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND (NOT sink_data(56))) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND (NOT sink_data(60))) AND (NOT sink_data(61))) AND (NOT sink_data(62)));
	s_wire_nios_system_addr_router_001_src_channel_5_494_dataout <= (((((((((((((((sink_data(47) AND sink_data(48)) AND (NOT sink_data(49))) AND (NOT sink_data(50))) AND (NOT sink_data(51))) AND (NOT sink_data(52))) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND (NOT sink_data(56))) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND (NOT sink_data(60))) AND (NOT sink_data(61))) AND (NOT sink_data(62)));
	s_wire_nios_system_addr_router_001_src_channel_6_522_dataout <= ((((NOT sink_data(59)) AND sink_data(60)) AND (NOT sink_data(61))) AND (NOT sink_data(62)));
	s_wire_nios_system_addr_router_001_src_channel_7_550_dataout <= (((((((((((NOT sink_data(52)) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND (NOT sink_data(56))) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND (NOT sink_data(60))) AND (NOT sink_data(61))) AND sink_data(62));
	sink_ready <= src_ready;
	src_channel <= ( wire_nios_system_addr_router_001_src_channel_87m_dataout & wire_nios_system_addr_router_001_src_channel_88m_dataout & wire_nios_system_addr_router_001_src_channel_89m_dataout & wire_nios_system_addr_router_001_src_channel_90m_dataout & s_wire_nios_system_addr_router_001_src_channel_7_550_dataout & wire_nios_system_addr_router_001_src_channel_92m_dataout & wire_nios_system_addr_router_001_src_channel_93m_dataout & wire_nios_system_addr_router_001_src_channel_94m_dataout);
	src_data <= ( sink_data(99 DOWNTO 90) & wire_nios_system_addr_router_001_src_data_95m_dataout & wire_nios_system_addr_router_001_src_data_96m_dataout & wire_nios_system_addr_router_001_src_data_97m_dataout & sink_data(86 DOWNTO 0));
	src_endofpacket <= sink_endofpacket;
	src_startofpacket <= sink_startofpacket;
	src_valid <= sink_valid;
	wire_w_sink_data_range120w(0) <= sink_data(39);
	wire_w_sink_data_range123w(0) <= sink_data(40);
	wire_nios_system_addr_router_001_src_channel_20m_dataout <= wire_w1w(0) AND NOT(s_wire_nios_system_addr_router_001_src_channel_1_382_dataout);
	wire_nios_system_addr_router_001_src_channel_21m_dataout <= s_wire_nios_system_addr_router_001_src_channel_0_354_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_1_382_dataout);
	wire_nios_system_addr_router_001_src_channel_28m_dataout <= s_wire_nios_system_addr_router_001_src_channel_1_382_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_2_410_dataout);
	wire_nios_system_addr_router_001_src_channel_32m_dataout <= wire_nios_system_addr_router_001_src_channel_20m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_2_410_dataout);
	wire_nios_system_addr_router_001_src_channel_33m_dataout <= wire_nios_system_addr_router_001_src_channel_21m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_2_410_dataout);
	wire_nios_system_addr_router_001_src_channel_39m_dataout <= s_wire_nios_system_addr_router_001_src_channel_2_410_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_3_438_dataout);
	wire_nios_system_addr_router_001_src_channel_40m_dataout <= wire_nios_system_addr_router_001_src_channel_28m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_3_438_dataout);
	wire_nios_system_addr_router_001_src_channel_44m_dataout <= wire_nios_system_addr_router_001_src_channel_32m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_3_438_dataout);
	wire_nios_system_addr_router_001_src_channel_45m_dataout <= wire_nios_system_addr_router_001_src_channel_33m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_3_438_dataout);
	wire_nios_system_addr_router_001_src_channel_51m_dataout <= wire_nios_system_addr_router_001_src_channel_39m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_4_466_dataout);
	wire_nios_system_addr_router_001_src_channel_52m_dataout <= wire_nios_system_addr_router_001_src_channel_40m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_4_466_dataout);
	wire_nios_system_addr_router_001_src_channel_53m_dataout <= s_wire_nios_system_addr_router_001_src_channel_3_438_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_4_466_dataout);
	wire_nios_system_addr_router_001_src_channel_56m_dataout <= wire_nios_system_addr_router_001_src_channel_44m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_4_466_dataout);
	wire_nios_system_addr_router_001_src_channel_57m_dataout <= wire_nios_system_addr_router_001_src_channel_45m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_4_466_dataout);
	wire_nios_system_addr_router_001_src_channel_63m_dataout <= wire_nios_system_addr_router_001_src_channel_51m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_5_494_dataout);
	wire_nios_system_addr_router_001_src_channel_64m_dataout <= wire_nios_system_addr_router_001_src_channel_52m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_5_494_dataout);
	wire_nios_system_addr_router_001_src_channel_65m_dataout <= wire_nios_system_addr_router_001_src_channel_53m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_5_494_dataout);
	wire_nios_system_addr_router_001_src_channel_66m_dataout <= s_wire_nios_system_addr_router_001_src_channel_4_466_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_5_494_dataout);
	wire_nios_system_addr_router_001_src_channel_68m_dataout <= wire_nios_system_addr_router_001_src_channel_56m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_5_494_dataout);
	wire_nios_system_addr_router_001_src_channel_69m_dataout <= wire_nios_system_addr_router_001_src_channel_57m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_5_494_dataout);
	wire_nios_system_addr_router_001_src_channel_75m_dataout <= wire_nios_system_addr_router_001_src_channel_63m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_6_522_dataout);
	wire_nios_system_addr_router_001_src_channel_76m_dataout <= wire_nios_system_addr_router_001_src_channel_64m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_6_522_dataout);
	wire_nios_system_addr_router_001_src_channel_77m_dataout <= wire_nios_system_addr_router_001_src_channel_65m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_6_522_dataout);
	wire_nios_system_addr_router_001_src_channel_78m_dataout <= wire_nios_system_addr_router_001_src_channel_66m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_6_522_dataout);
	wire_nios_system_addr_router_001_src_channel_80m_dataout <= wire_nios_system_addr_router_001_src_channel_68m_dataout OR s_wire_nios_system_addr_router_001_src_channel_6_522_dataout;
	wire_nios_system_addr_router_001_src_channel_81m_dataout <= wire_nios_system_addr_router_001_src_channel_69m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_6_522_dataout);
	wire_nios_system_addr_router_001_src_channel_82m_dataout <= s_wire_nios_system_addr_router_001_src_channel_5_494_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_6_522_dataout);
	wire_nios_system_addr_router_001_src_channel_87m_dataout <= wire_nios_system_addr_router_001_src_channel_75m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_7_550_dataout);
	wire_nios_system_addr_router_001_src_channel_88m_dataout <= wire_nios_system_addr_router_001_src_channel_76m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_7_550_dataout);
	wire_nios_system_addr_router_001_src_channel_89m_dataout <= wire_nios_system_addr_router_001_src_channel_77m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_7_550_dataout);
	wire_nios_system_addr_router_001_src_channel_90m_dataout <= wire_nios_system_addr_router_001_src_channel_78m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_7_550_dataout);
	wire_nios_system_addr_router_001_src_channel_92m_dataout <= wire_nios_system_addr_router_001_src_channel_80m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_7_550_dataout);
	wire_nios_system_addr_router_001_src_channel_93m_dataout <= wire_nios_system_addr_router_001_src_channel_81m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_7_550_dataout);
	wire_nios_system_addr_router_001_src_channel_94m_dataout <= wire_nios_system_addr_router_001_src_channel_82m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_7_550_dataout);
	wire_nios_system_addr_router_001_src_data_24m_dataout <= s_wire_nios_system_addr_router_001_src_channel_0_354_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_1_382_dataout);
	wire_nios_system_addr_router_001_src_data_36m_dataout <= wire_nios_system_addr_router_001_src_data_24m_dataout OR s_wire_nios_system_addr_router_001_src_channel_2_410_dataout;
	wire_nios_system_addr_router_001_src_data_37m_dataout <= wire_w2w(0) AND NOT(s_wire_nios_system_addr_router_001_src_channel_2_410_dataout);
	wire_nios_system_addr_router_001_src_data_47m_dataout <= s_wire_nios_system_addr_router_001_src_channel_2_410_dataout OR s_wire_nios_system_addr_router_001_src_channel_3_438_dataout;
	wire_nios_system_addr_router_001_src_data_48m_dataout <= wire_nios_system_addr_router_001_src_data_36m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_3_438_dataout);
	wire_nios_system_addr_router_001_src_data_49m_dataout <= wire_nios_system_addr_router_001_src_data_37m_dataout OR s_wire_nios_system_addr_router_001_src_channel_3_438_dataout;
	wire_nios_system_addr_router_001_src_data_59m_dataout <= wire_nios_system_addr_router_001_src_data_47m_dataout OR s_wire_nios_system_addr_router_001_src_channel_4_466_dataout;
	wire_nios_system_addr_router_001_src_data_60m_dataout <= wire_nios_system_addr_router_001_src_data_48m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_4_466_dataout);
	wire_nios_system_addr_router_001_src_data_61m_dataout <= wire_nios_system_addr_router_001_src_data_49m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_4_466_dataout);
	wire_nios_system_addr_router_001_src_data_71m_dataout <= wire_nios_system_addr_router_001_src_data_59m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_5_494_dataout);
	wire_nios_system_addr_router_001_src_data_72m_dataout <= wire_nios_system_addr_router_001_src_data_60m_dataout OR s_wire_nios_system_addr_router_001_src_channel_5_494_dataout;
	wire_nios_system_addr_router_001_src_data_73m_dataout <= wire_nios_system_addr_router_001_src_data_61m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_5_494_dataout);
	wire_nios_system_addr_router_001_src_data_83m_dataout <= wire_nios_system_addr_router_001_src_data_71m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_6_522_dataout);
	wire_nios_system_addr_router_001_src_data_84m_dataout <= wire_nios_system_addr_router_001_src_data_72m_dataout AND NOT(s_wire_nios_system_addr_router_001_src_channel_6_522_dataout);
	wire_nios_system_addr_router_001_src_data_85m_dataout <= wire_nios_system_addr_router_001_src_data_73m_dataout OR s_wire_nios_system_addr_router_001_src_channel_6_522_dataout;
	wire_nios_system_addr_router_001_src_data_95m_dataout <= wire_nios_system_addr_router_001_src_data_83m_dataout OR s_wire_nios_system_addr_router_001_src_channel_7_550_dataout;
	wire_nios_system_addr_router_001_src_data_96m_dataout <= wire_nios_system_addr_router_001_src_data_84m_dataout OR s_wire_nios_system_addr_router_001_src_channel_7_550_dataout;
	wire_nios_system_addr_router_001_src_data_97m_dataout <= wire_nios_system_addr_router_001_src_data_85m_dataout OR s_wire_nios_system_addr_router_001_src_channel_7_550_dataout;

 END RTL; --nios_system_addr_router_001
--synopsys translate_on
--VALID FILE
