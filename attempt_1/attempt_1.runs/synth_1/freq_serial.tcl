# 
# Synthesis run script generated by Vivado
# 

set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
create_project -in_memory -part xc7z020clg484-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir C:/Users/s02so/05062016_FYP/attempt_1/attempt_1.cache/wt [current_project]
set_property parent.project_path C:/Users/s02so/05062016_FYP/attempt_1/attempt_1.xpr [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property board_part em.avnet.com:zed:part0:1.3 [current_project]
set_property ip_repo_paths c:/Users/s02so/Desktop/example/impl [current_project]
read_verilog -library xil_defaultlib {
  C:/Users/s02so/05062016_FYP/ip/hdl/verilog/freq_serial_mux_224to1_sel8_37_1.v
  C:/Users/s02so/05062016_FYP/ip/hdl/verilog/freq_serial_FREQ_PERIPH_BUS_s_axi.v
  C:/Users/s02so/05062016_FYP/ip/hdl/verilog/freq_serial.v
}
foreach dcp [get_files -quiet -all *.dcp] {
  set_property used_in_implementation false $dcp
}

synth_design -top freq_serial -part xc7z020clg484-1


write_checkpoint -force -noxdef freq_serial.dcp

catch { report_utilization -file freq_serial_utilization_synth.rpt -pb freq_serial_utilization_synth.pb }
