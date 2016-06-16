# This file is automatically generated.
# It contains project source information necessary for synthesis and implementation.

# Block Designs: bd/block_design1/block_design1.bd
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==block_design1 || ORIG_REF_NAME==block_design1}]

# IP: bd/block_design1/ip/block_design1_processing_system7_0_0/block_design1_processing_system7_0_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==block_design1_processing_system7_0_0 || ORIG_REF_NAME==block_design1_processing_system7_0_0}]

# IP: bd/block_design1/ip/block_design1_processing_system7_0_axi_periph_0/block_design1_processing_system7_0_axi_periph_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==block_design1_processing_system7_0_axi_periph_0 || ORIG_REF_NAME==block_design1_processing_system7_0_axi_periph_0}]

# IP: bd/block_design1/ip/block_design1_rst_processing_system7_0_100M_0/block_design1_rst_processing_system7_0_100M_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==block_design1_rst_processing_system7_0_100M_0 || ORIG_REF_NAME==block_design1_rst_processing_system7_0_100M_0}]

# IP: bd/block_design1/ip/block_design1_freq_serial_0_0/block_design1_freq_serial_0_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==block_design1_freq_serial_0_0 || ORIG_REF_NAME==block_design1_freq_serial_0_0}]

# IP: bd/block_design1/ip/block_design1_auto_pc_0/block_design1_auto_pc_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==block_design1_auto_pc_0 || ORIG_REF_NAME==block_design1_auto_pc_0}]

# XDC: bd/block_design1/ip/block_design1_processing_system7_0_0/block_design1_processing_system7_0_0.xdc
set_property DONT_TOUCH TRUE [get_cells [split [join [get_cells -hier -filter {REF_NAME==block_design1_processing_system7_0_0 || ORIG_REF_NAME==block_design1_processing_system7_0_0}] {/inst }]/inst ]]

# XDC: bd/block_design1/ip/block_design1_rst_processing_system7_0_100M_0/block_design1_rst_processing_system7_0_100M_0_board.xdc
set_property DONT_TOUCH TRUE [get_cells [split [join [get_cells -hier -filter {REF_NAME==block_design1_rst_processing_system7_0_100M_0 || ORIG_REF_NAME==block_design1_rst_processing_system7_0_100M_0}] {/U0 }]/U0 ]]

# XDC: bd/block_design1/ip/block_design1_rst_processing_system7_0_100M_0/block_design1_rst_processing_system7_0_100M_0.xdc
#dup# set_property DONT_TOUCH TRUE [get_cells [split [join [get_cells -hier -filter {REF_NAME==block_design1_rst_processing_system7_0_100M_0 || ORIG_REF_NAME==block_design1_rst_processing_system7_0_100M_0}] {/U0 }]/U0 ]]

# XDC: bd/block_design1/ip/block_design1_rst_processing_system7_0_100M_0/block_design1_rst_processing_system7_0_100M_0_ooc.xdc

# XDC: bd/block_design1/ip/block_design1_freq_serial_0_0/constraints/freq_serial_ooc.xdc

# XDC: bd/block_design1/ip/block_design1_auto_pc_0/block_design1_auto_pc_0_ooc.xdc

# XDC: bd/block_design1/block_design1_ooc.xdc
