

function(AddXamlSources baseTarget xamlSources)

	foreach(xamlSource ${xamlSources})
		get_filename_component(fileName ${xamlSource} ABSOLUTE)
		get_filename_component(targetName ${xamlSource} NAME_WLE)
		set(outputName ${CMAKE_BINARY_DIR}/XamlSources/${targetName}.hpp)
		add_custom_command(OUTPUT ${outputName}
			COMMAND ${xutLocation} -i ${fileName} -o ${outputName}
			DEPENDS ${fileName}
		)
		add_custom_target(${targetName}
			DEPENDS ${outputName}
		)
		set_source_files_properties(${outputName} PROPERTIES GENERATED TRUE)
		add_dependencies(${baseTarget} ${targetName})
		add_dependencies( ${targetName} xut)
		target_include_directories(${baseTarget} PRIVATE ${CMAKE_BINARY_DIR}/XamlSources/)
	endforeach()

endfunction()
