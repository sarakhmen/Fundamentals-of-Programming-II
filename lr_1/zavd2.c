//Не використання realloc в нашому випадку повністю аргументовано, адже realloc -
//це зайві втрати швидкодії.
//Визивати функцію realloc варто в тому випадку, якщо кількість 
//елементів у масиві nameval, наприклад, більш ніж у 2 рази менша за максимальну кількість, щоб
//заощаджувати пам'ять