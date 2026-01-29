Lizi Luo Assignment: Program 1 - SearchAlgorithms Comparison Date: January 28, 2026 SID: 862605965

#### Search Algorithms  Performance Analysis Report

###### Based on the code we can analyze Search Algorithms time complexity:

Linear Search: O(n*m)

Binary Search:O(nlogn ~sort~ + m log n ~search~)

![complexity_comparison](/Users/digby/Documents/10C/image/report/complexity_comparison.png)

| **Sightings** | **Signatures** | **Linear** | **Binary** | **Speedup** |
| ------------- | -------------- | ---------- | ---------- | ----------- |
| **20000**     | 4000           | 8470.6     | 3860.31    | 2.19        |
| **10000**     | 2000           | 4059.97    | 1610.33    | 2.52        |
| **5000**      | 1000           | 1994.95    | 781.24     | 2.55        |
| **2000**      | 400            | 608.32     | 284.25     | 2.14        |
| **1000**      | 200            | 343.57     | 134.79     | 2.55        |
| **500**       | 100            | 123.93     | 61.33      | 2.02        |
| **200**       | 40             | 27.18      | 22.5       | 1.21        |
| **100**       | 20             | 9.29       | 10.86      | 0.86        |
| **50**        | 10             | 2.24       | 6.72       | 0.33        |

![plot1_comparison](/Users/digby/Documents/10C/image/report/plot1_comparison.png)

##### Based on the test if the n is less than 200, Binary Search might slower than Linear Search.

###### Why Binary Search Doesn't Achieve Theoretical Advantage Immediately

might beacause sorting : One-time O(n log n) cost is significant for small datasets



###### Test Environment

Hardware: - Processor: Apple Silicon (ARM64) - Memory: 16G

Software: - OS: macOS 26 (Darwin 25.2.0) - Compiler: g++ (Apple clang) - Flags:

-std=c++11 -Wall -Werror 

Data Collection: - Test runs: 3 per configuration - Total configurations: 27 - Total measurements: 54