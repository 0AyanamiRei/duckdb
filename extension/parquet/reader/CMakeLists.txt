add_library_unity(
  duckdb_parquet_readers
  OBJECT
  decimal_column_reader.cpp
  expression_column_reader.cpp
  list_column_reader.cpp
  row_number_column_reader.cpp
  string_column_reader.cpp
  struct_column_reader.cpp
  variant_column_reader.cpp)

add_subdirectory(variant)

set(PARQUET_EXTENSION_FILES
    ${PARQUET_EXTENSION_FILES} $<TARGET_OBJECTS:duckdb_parquet_readers>
    PARENT_SCOPE)
