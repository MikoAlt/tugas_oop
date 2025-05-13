# Tabel Perbandingan

anggota kelompok
- Ali Reza
2306211471
- Fadlin Alwan H H
2306224335
- Mikola Syabila
2306266741
- Muhammad Alif Iqbal 
- 2306206654

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
STD, Quick, Heap, dan Merge sort memiliki performa yang terbaik karena kompleksitas waktu yang lebih rendah, yakni O(n logn). disini STD sort memiliki waktu yang tersingkat diseluruh benchmark karena STD Sort telah dioptimisasi dalam standard library algorithm cpp.

**3. Algoritma Terburuk:**
Bubble Sort menjadi sorting yang terburuk. Untuk ukuran data yang sangat besar seperti pada contoh yang berukuran 47805, waktu yang dibutuhkan hingga lebih dari 100 detik hal tersebut disebabkan karena algoritma ini akan membandingkan setiap elemen secara berulang tanpa optimasi. Kemudian Algoritma terburuk kedua adalah Insertion sort karena kompleksitas waktu keduanya mirip, yakni O(n^2).

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
Sama seperti key sorting "Name" untuk ukuran data yang lebih besar maka akan mengakibatkan waktu pengolaha yang lebih lama. Perbedaan kecepatan sorting antara jenis key berasal dari kecepatan comparing functionnya.

**2. Algoritma Terbaik:**
STD, Quick, Heap, dan Merge sort menjadi sorting yang terbaik karena waktu pengolahan yang konsisten, terutama untuk dataset besar. STD sort lebih unggul seperti biasa karena telah dioptimisasi dalam standard library.

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
STD, Quick, Heap, dan Merge Sort akan tetap unggul, dengan waktu pengolahan yang cepat bahkan untuk data besar. STD sort tetap unggul di setiap benchmark karena telah dioptimisasi di standard library algorithm.

**3. Algoritma Terburuk:**
Bubble Sort kembali menjadi jenis sorting yang paling tidak efisien dalam prosesnya bubble sorting membutuhkan waktu lebih dari 86 detik untuk data berukuran 47805.



## Kesimpulan
Perbedaan waktu pada pengolahan data terjadi karena setiap algoritma memiliki kompleksitas waktu yang berbeda, seperti berikut

- Bubble Sort memiliki Kompleksitas waktu $O(n^2)$ dan karena hal ini bubble sort akan sangat lambat untuk data yang besar. Hal ini diamplifikasi oleh dengan tidak menggunakan compiler optimization.

- Insertion Sort memiliki Kompleksitas waktu $O(n^2)$ walaupun kompleksitasnya sama tetapi pada data set kecil akan lebih cepat daripada Bubble Sort.

- Merge Sort dan Quick Sort memiliki Kompleksitas waktu $O(n _log_n)$ dan akan optimal untuk data yang besar. Algoritma ini juga stabil, sehingga kecepatan sortingnya akan selalu sama pada besar data yang sama.

- Heap sort disini memilki rata rata kecepatan yang signifikan lebih lambat dibanding Mergesort dan quick sort walaupun Heapsort juga memilki kompleksitas waktu O(n logn). Hal ini dapat disebabkan oleh proses Heapification yang memerlukan proses O(1) yang lebih lama dibanding merge sort maupun quick sort. Hal ini dapat dimitigasi dengan menggunakan compiler optimization

- STD Sort akan Memanfaatkan algoritma yang sudah dioptimasi.

Algoritma Terbaik:
STD Sort menjadi jenis sorting yang konsisten untuk segala kondisi dan menjadi pilihan terbaik karena implementasinya yang sudah dioptimasi. selain itu Merge Sort juga menjadi pilihan yang sangat baik, terutama untuk data besar.

Algoritma Terburuk:
Bubble Sort adalah algoritma paling tidak efisien akibat banyaknya operasi yang tidak perlu (misalnya, membandingkan elemen yang sudah terurut).

## Grafik perbandingan
![WhatsApp Image 2025-05-13 at 22.53.19](https://hackmd.io/_uploads/H1gy01WZex.jpg)

![WhatsApp Image 2025-05-13 at 23.01.05](https://hackmd.io/_uploads/r1XJA1-Wgx.jpg)
