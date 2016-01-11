#************************************************************
# THIS IS A WIZARD-GENERATED FILE.                           
#
# Version 13.0.1 Build 232 06/12/2013 Service Pack 1 SJ Web Edition
#
#************************************************************

# Copyright (C) 1991-2013 Altera Corporation
# Your use of Altera Corporation's design tools, logic functions 
# and other software and tools, and its AMPP partner logic 
# functions, and any output files from any of the foregoing 
# (including device programming or simulation files), and any 
# associated documentation or information are expressly subject 
# to the terms and conditions of the Altera Program License 
# Subscription Agreement, Altera MegaCore Function License 
# Agreement, or other applicable license agreement, including, 
# without limitation, that your use is for the sole purpose of 
# programming logic devices manufactured by Altera and sold by 
# Altera or its authorized distributors.  Please refer to the 
# applicable agreement for further details.



# Clock constraints

create_clock -name "clock50Mhz" -period 20.000ns [get_ports {CLOCK_50}] -waveform {0.000 10.000}


# Automatically constrain PLL and other generated clocks
derive_pll_clocks -create_base_clocks
derive_clocks -period 40.000ns -waveform {0.000 20.000}

# Automatically calculate clock uncertainty to jitter and other effects.
#derive_clock_uncertainty
# Not supported for family Cyclone II

# tsu/th constraints

# tco constraints

# tpd constraints

#set_max_delay 12.000ns -from [get_ports {CLOCK_50}] -to [get_ports {SRam_LB_N SRam_OE_N SRam_UB_N SRam_WE_N SRam_CE_N SRam_DQ SRAM_ADDR}]
#set_min_delay 8.000ns -from [get_ports {CLOCK_50}] -to [get_ports {SRam_LB_N SRam_OE_N SRam_UB_N SRam_WE_N SRam_CE_N SRam_DQ SRAM_ADDR}]


set_max_skew  -to [get_ports {SRam_LB_N SRam_OE_N SRam_UB_N SRam_WE_N SRam_CE_N SRam_DQ[*] SRAM_ADDR[*]}] 0.5
#report_max_skew -panel_name "Report Max Skew" -npaths 10 -detail path_only	