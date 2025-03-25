idf_component_register(
    SRCS "src/display_task.c" "src/input_task.c"
    INCLUDE_DIRS "include"
    REQUIRES myhal app_logic freertos
)