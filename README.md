# Standalone Version of Digit Rounding for ease of compression assessment
## This is a standalone version of Digit rounding compressor, which was integrated with HDF5 filter in https://github.com/CNES/Digit_Rounding

To confirm the correctness of our implementation, the evaluation results based on climate simulation datasets (https://sdrbench.github.io/) are shown below:
* Original DR refers to the original digit rounding code (https://github.com/CNES/Digit_Rounding)
* digitroundingZ refers to the code of this repo.
* PSNR: peask signal noise to ratio
* Max Relative Error: max error of the point-wise relative error
* Compressed Data Size: in Bytes.
* Compression Ratio: Original Size / Compressed Size

<font size=5>The slight difference (around 1% in general) on compression ratio might be due to different lossless compressor we used: we are using Zlib while the orginal version is using Gzip embedded in HDF5. All other impelemntations should be exactly the same. <font/>

Field: CLDLOW_1_1800_3600

|	| PSNR |	|	Max Relative Error	| |	Compressed Data Size	| |	Compression Ratio	| |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| nsd | Original DR	| digitroundingZ |	Original DR	| digitroundingZ |	Original DR |	digitroundingZ |	Original DR |	digitroundingZ |
| 2 |	52.587367	| 52.587367	| 0.041659 | 0.041659 | 2057702	| 2084242	| 12.6	| 12.44 |
| 3	| 70.655662	| 70.655662	| 0.004308 | 0.004308 | 4813880	| 4944725	| 5.385	| 5.24 |
| 4	| 94.736202	| 94.736202	| 0.000402 | 0.000402 | 7918834	| 8095942	| 3.274	| 3.202 |
| 5	| 112.798155| 112.798155 | 4.3E-05 | 4.3E-05| 	10029522	| 10174900	| 2.585	| 2.55 |
| 6	| 130.850663| 130.850663 | 4E-06 | 4E-06	| 12805616| 	12942513	| 2.0243	| 2.003 |

Field: CLDHGH_1_1800_3600

|	| PSNR |	|	Max Relative Error	| |	Compressed Data Size	| |	Compression Ratio	| |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| nsd | Original DR	| digitroundingZ |	Original DR	| digitroundingZ |	Original DR |	digitroundingZ |	Original DR |	digitroundingZ |
| 2	| 53.276963	| 53.276963	| 0.041659	| 0.041659	| 2257978	| 2293301	| 11.48	| 11.30| 
| 3	| 71.344325	| 71.344325	| 0.004309	| 0.004309	| 5348641	| 5516942	| 4.85	| 4.7|
| 4	| 95.405864	| 95.405864	| 0.000373	| 0.000373	| 8540314	| 8779464	| 3.04	| 2.95|
| 5	| 113.466171	| 113.466171	| 4.3E-05	| 4.3E-05	| 10734906	| 10926706	| 2.41	| 2.37|
| 6	| 131.537219	| 131.537219	| 4E-06	| 4E-06	| 13789233	| 13972567	| 1.88	| 1.86|

Field: CLDHGH_1_1800_3600

|	| PSNR |	|	Max Relative Error	| |	Compressed Data Size	| |	Compression Ratio	| |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| nsd | Original DR	| digitroundingZ |	Original DR	| digitroundingZ |	Original DR |	digitroundingZ |	Original DR |	digitroundingZ |

