

function(AddXamlSources baseTarget xamlSources)

	foreach(xamlSource ${xamlSources})
		get_filename_component(fileName ${xamlSource} ABSOLUTE)
		get_filename_component(targetName ${xamlSource} NAME_WLE)
		set(outputName ${CMAKE_BINARY_DIR}/XamlSources/${targetName}.hpp)
		message(STATUS ${outputName})
		add_custom_command(OUTPUT ${outputName}
			COMMAND ${xutLocation} -i ${fileName} -o ${outputName}
			MAIN_DEPENDENCY ${fileName}
		)
		add_custom_target(${targetName}
			DEPENDS ${outputName}
		)
		set_source_files_properties(${outputName} PROPERTIES GENERATED TRUE)
		add_dependencies(${baseTarget} ${targetName})
		target_include_directories(${baseTarget} PRIVATE ${CMAKE_BINARY_DIR}/XamlSources/)
	endforeach()

endfunction()
