# xut

xut stands for Xaml Under Testing and was originally made as a method for testing input xaml files against the OpenXaml library. It has since evolved and is the primary way of compiling xaml files down into hpp files that the user project can link against.

In order to add a new control, it must be added in three places.

1. The OpenXaml library (the base class file)
2. The XamlStandard.xsd file (verifies xaml syntax)
3. xut xaml elements (converts to valid hpp syntax)

This tool will eventually need to support multiple output languages, so the formatter file is specific to cpp right now.