---
title: 'Report '

---

# Tabel Perbandingan

**Note:**
Hasil data benchmark yang kami lakukan,  tidak menggunakan compiler Optimization yang akan mempengaruhi waktu proses pengolahan pada semua jenis sorting. 

## Tabel dan Analisis untuk Key Sorting "name" Dengan Data Size yang Berbeda
### Key: Name ; Data Size: 1000
| Algoritma   | Waktu Proses (ms) |
|-------------|-------------------|
| Bubble      | 59                |
| Insertion   | 17                |
| Merge       | 1                 |
| Quick       | 0                 |
| Heap        | 1                 |
| STD         | 0                 |



### Key: Name ; Data Size: 10000
| Algoritma   | Waktu Proses (ms) |
|-------------|-------------------|
| Bubble      | 4681              |
| Insertion   | 1791              |
| Merge       | 14                |
| Quick       | 12                |
| Heap        | 22                |
| STD         | 11                |


### Key: Name, Data Size: 47805
| Algoritma   | Waktu Proses (ms) |
|-------------|-------------------|
| Bubble      | 103439            |
| Insertion   | 41583             |
| Merge       | 81                |
| Quick       | 81                |
| Heap        | 128               |
| STD         | 76                |

### *Analisis*
**1. Perbedaan Waktu Pengolahan:**
Ukuran data yang lebih besar akan membutuhkan waktu pengolahan yang lebih lama. Hal tersebut disebabkan karena semakin banyak data maka semakin banyak elemen yang harus dibandingkan dan diurutkan dan pada pada dataset yang besar algoritma seperti Bubble Sort akan memerlukan lebih banyak iterasi dibandingkan algoritma lain seperti Merge Sort atau STD Sort.

**2. Algoritma Terbaik:**
STD dan Merge Sort lebih cepat waktu pengolahannya untuk semua ukuran data dibanding yang lain. Hal tersebut terjadi karena keduanya menggunakan pendekatan yang efisien sebagai contoh Merge Sort akan membagi data menjadi bagian-bagian kecil sebelum mengurutkannya, sementara STD  diimplementasikan dengan algoritma yang sudah optimal.

**3. Algoritma Terburuk:**
Bubble Sort menjadi sorting yang terburuk. Untuk ukuran data yang sangat besar seperti pada contoh yang berukuran 47805, waktu yang dibutuhkan hingga lebih dari 100 detik hal tersebut disebabkan karena algoritma ini akan membandingkan setiap elemen secara berulang tanpa optimasi.

## Tabel dan Analisis untuk Key Sorting "Population" Dengan Data Size yang Berbeda
### Key: Population, Data Size: 1000
| Algoritma   | Waktu Proses (ms) |
|-------------|-------------------|
| Bubble      | 36                |
| Insertion   | 17                |
| Merge       | 0                 |
| Quick       | 0                 |
| Heap        | 1                 |
| STD         | 0                 |


### Key: Population, Data Size: 10000
| Algoritma   | Waktu Proses (ms) |
|-------------|-------------------|
| Bubble      | 3845              |
| Insertion   | 1673              |
| Merge       | 13                |
| Quick       | 11                |
| Heap        | 21                |
| STD         | 10                |


### Key: Population, Data Size: 47805
| Algoritma   | Waktu Proses (ms) |
|-------------|-------------------|
| Bubble      | 92389             |
| Insertion   | 37979             |
| Merge       | 85                |
| Quick       | 80                |
| Heap        | 109               |
| STD         | 54                |



### *Analisis*
**1. Perbedaan Waktu Pengolahan:**
Sama seperti key sorting "Name" untuk ukuran data yang lebih besar maka akan mengakibatkan waktu pengolaha yang lebih lama. Namun, pada key Population yang yang datanya berupa angka,  membuat algoritma optimal untuk data numerik, seperti Quick Sort, akan menjadi lebih unggul.

**2. Algoritma Terbaik:**
Merge Sort dan STD Sort menjadi sorting yang terbaik karena waktu pengolahan yang konsisten, terutama untuk dataset besar.

**3. Algoritma Terburuk:**
Lagi-lagi, Bubble Sort menjadi sorting yang terburuk. Untuk ukuran data 47805 karena waktu pengolahannya hampir mencapai 93 detik.

## Tabel dan Analisis untuk Key Sorting "Latitude" Dengan Data Size yang Berbeda

### Key: Latitude, Data Size: 1000
| Algoritma   | Waktu Proses (ms) |
|-------------|-------------------|
| Bubble      | 42                |
| Insertion   | 16                |
| Merge       | 1                 |
| Quick       | 0                 |
| Heap        | 1                 |
| STD         | 0                 |


### Key: Latitude, Data Size: 10000
| Algoritma   | Waktu Proses (ms) |
|-------------|-------------------|
| Bubble      | 3836              |
| Insertion   | 1638              |
| Merge       | 13                |
| Quick       | 12                |
| Heap        | 20                |
| STD         | 10                |


### Key: Latitude, Data Size: 47805
| Algoritma   | Waktu Proses (ms) |
|-------------|-------------------|
| Bubble      | 86168             |
| Insertion   | 35300             |
| Merge       | 78                |
| Quick       | 74                |
| Heap        | 108               |
| STD         | 61                |


### *Analisis*
**1. Analisis Perbedaan Waktu Pengolahan:**
Sama dengan key lainnya semakin besar ukuran data maka waktu pengolahan akan meningkat. Namun, karena data Latitude juga berupa angka (seperti population), algoritma numerik seperti Quick Sort memiliki kinerja yang baik.

**2. Algoritma Terbaik:**
STD dan Merge Sort akan tetap unggul, dengan waktu pengolahan yang cepat bahkan untuk data besar.

**3. Algoritma Terburuk:**
Bubble Sort kembali menjadi jenis sorting yang paling tidak efisien dalam prosesnya bubble sorting membutuhkan waktu lebih dari 86 detik untuk data berukuran 47805.



## Kesimpulan
Perbedaan waktu pada pengolahan data terjadi karena setiap algoritma memiliki kompleksitas waktu yang berbeda, seperti berikut

- Bubble Sort memiliki Kompleksitas waktu $O(n^2)$ dan karena hal ini bubble sort akan sangat lambat untuk data yang besar.

- Insertion Sort memiliki Kompleksitas waktu $O(n^2)$ walaupun kompleksitasnya sama tetapi pada data set kecil akan lebih cepat daripada Bubble Sort.

- Merge Sort dan Quick Sort memiliki Kompleksitas waktu $O(n _log_n)$ dan akan optimal untuk data yang besar.

- STD Sort akan Memanfaatkan algoritma yang sudah dioptimasi.

Algoritma Terbaik:
STD Sort menjadi jenis sorting yang konsisten untuk segala kondisi dan menjadi pilihan terbaik karena implementasinya yang sudah dioptimasi. selain itu Merge Sort juga menjadi pilihan yang sangat baik, terutama untuk data besar.

Algoritma Terburuk:
Bubble Sort adalah algoritma paling tidak efisien akibat banyaknya operasi yang tidak perlu (misalnya, membandingkan elemen yang sudah terurut).
