# Standalone Version of Digit Rounding for ease of compression assessment
## This is a standalone version of Digit rounding compressor, which was integrated with HDF5 filter in https://github.com/CNES/Digit_Rounding

The evaluation results based on climate simulation datasets (https://sdrbench.github.io/) are shown below:
* Original DR refers to the original digit rounding code (https://github.com/CNES/Digit_Rounding)
* digitroundingZ refers to the code of this repo.

Field: CLDLOW_1_1800_3600

|	| PSNR |	|	Max Point-wise Relative Error	| |	Compressed Data Size	| |	Compression Ratio	| |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| nsd | Original DR	| digitroundingZ |	Original DR	| digitroundingZ |	Original DR |	digitroundingZ |	Original DR |	digitroundingZ |
| 2 |	52.587367	| 52.587367	| 0.041659 | 0.041659 | 2057702	| 2084242	| 12.5976	| 12.4372
| 3	| 70.655662	| 70.655662	| 0.004308 | 0.004308 | 4813880	| 4944725	| 5.3849	| 5.2424
| 4	| 94.736202	| 94.736202	| 0.000402 | 0.000402 | 7918834	| 8095942	| 3.2735	| 3.2019
| 5	| 112.798155| 112.798155 | 4.3E-05 | 4.3E-05| 	10029522	| 10174900	| 2.5846	| 2.5476
| 6	| 130.850663| 130.850663 | 4E-06 | 4E-06	| 12805616| 	12942513	| 2.0243	| 2.0029

