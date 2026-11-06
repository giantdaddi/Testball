if(CONFIG_TB_PROBE)
  zephyr_library()
  zephyr_library_sources(src/probe.c)
endif()
