# Tugas OOP
---
Member List
- Ali Reza - 2306211471
- Mikola Syabila - 2306266741
- Fadlin Alwan Hanafi - 2306224335
- Muhammad Alif Iqbal - 2306206654
---

Program ini adalah sebuah program dengan bahasa C++ yang bertujuan untuk membuat CLI yang digunakan untuk melakukan sorting file CSV dengan beberapa algoritma sorting seperti heap sort, bubble sort, insertion sort, quick sort, merge sort, dan std sort. 

Dataset didapat dari website:
https://simplemaps.com/data/world-cities

Pastikan file CSV berada pada root.

---

Cara Membuild Program
-  Clone Repository
```bash
git clone https://github.com/MikoAlt/tugas_oop.git
```
- Build Dengan CMAKE
```
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
```
- Run Program
```powershell
./build/debug/citysort.exe -a <algo> -k <key> [-r] [-n N]

Options:
  -a <algo>         : Sorting algorithm. Required.
                      <algo>: bubble|insertion|merge|quick|heap|std
  -k <key>          : Sorting key (column). Required.
                      <key>: name|country|population|lat|lng
  -r                : Reverse sort order (descending). Optional.
  -n N              : Print only the first N rows. Optional. N must be > 0.
  --performace-test  -P : Run performance logging on all algorithm (this will ignore every other flags).
```