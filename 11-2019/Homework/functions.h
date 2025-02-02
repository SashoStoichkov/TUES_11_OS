//------------------------------------------------------------------------
// FUNCTION: lines_in_file
// Брои редовете във файл.
// PARAMETERS:
// -> име на файл
//------------------------------------------------------------------------
int lines_in_file(char *filename);

//------------------------------------------------------------------------
// FUNCTION: chars_in_file
// Брои символите във файл.
// PARAMETERS:
// -> име на файл
//------------------------------------------------------------------------
int chars_in_file(char *filename);

//------------------------------------------------------------------------
// FUNCTION: return_whole_file
// Извежда целия файл, ако той има 10 реда или по-малко
// PARAMETERS:
// -> име на файл
//------------------------------------------------------------------------
void return_whole_file(char *filename);

//------------------------------------------------------------------------
// FUNCTION: add_file_header
// Извежда името на файла във формат ==> име <==
// PARAMETERS:
// -> име на файл
// -> индекс на конзолен аргумент
//------------------------------------------------------------------------
void add_file_header(char *filename, int argc_index);

//------------------------------------------------------------------------
// FUNCTION: add_stdin_header
// Извежда ==> standard input <==
// PARAMETERS:
// -> None
//------------------------------------------------------------------------
void add_stdin_header(int argc_index);

//------------------------------------------------------------------------
// FUNCTION: all_arguments_are_dashes
// Проверка дали всички параметри са "-"
// PARAMETERS:
// -> брой конзолни аргументи
// -> списък от конзолни аргументи
//------------------------------------------------------------------------
int all_arguments_are_dashes(int argc, char *argv[]);

//------------------------------------------------------------------------
// FUNCTION: write_file_in_array
// Записва целия файл в масив
// PARAMETERS:
// -> име на файл
// -> масив, в който да се запише файла
//------------------------------------------------------------------------
void write_file_in_array(char *filename, char *file_arr);

//------------------------------------------------------------------------
// FUNCTION: last_ten_lines_char_count
// Брои символите на последните 10 реда от файл
// PARAMETERS:
// -> масив от всички символи във файла
// -> Брой на всички символи във файла
//------------------------------------------------------------------------
int last_ten_lines_char_count(char *file_arr, int sizeof_file_arr);

//------------------------------------------------------------------------
// FUNCTION: get_last_ten_lines
// Записва последните 10 реда в масив
// PARAMETERS:
// -> масив от всички символи във файла
// -> Брой на всички символи във файла
// -> масив, в който да се запишат последните 10 реда
//------------------------------------------------------------------------
void get_last_ten_lines(char *file_arr, int sizeof_file_arr, char *last_ten);

//------------------------------------------------------------------------
// FUNCTION: return_last_ten_lines_of_file
// Извежда последните 10 реда от файл
// PARAMETERS:
// -> име на файл
//------------------------------------------------------------------------
void return_last_ten_lines_of_file(char *filename);

//------------------------------------------------------------------------
// FUNCTION: stdin_input
// Извежда последните 10 реда от стандартния вход
// PARAMETERS:
// -> None
//------------------------------------------------------------------------
void stdin_input();

//------------------------------------------------------------------------
// FUNCTION: no_such_file_or_directory_error
// Извежда грешка на стандартния изход за грешка за неналичие на файл
// PARAMETERS:
// -> име на файл
//------------------------------------------------------------------------
void no_such_file_or_directory_error(char *filename);

//------------------------------------------------------------------------
// FUNCTION: is_a_directory_error
// Извежда грешка на стандартния изход за грешка ако е подадена директория
// PARAMETERS:
// -> име на файл
//------------------------------------------------------------------------
void is_a_directory_error(char *filename);

//------------------------------------------------------------------------
// FUNCTION: input_output_error
// Извежда грешка на стандартния изход за грешка при затваряне на файл
// PARAMETERS:
// -> име на файл
//------------------------------------------------------------------------
void input_output_error(char *filename);
