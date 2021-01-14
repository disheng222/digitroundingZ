# Standalone Version of Digit Rounding for ease of compression assessment
## This is a standalone version of Digit rounding compressor, which was integrated with HDF5 filter in https://github.com/CNES/Digit_Rounding

To confirm the correctness of our implementation, the evaluation results based on climate simulation datasets (https://sdrbench.github.io/) are shown below:
* 'Original DR' refers to the original digit rounding code (https://github.com/CNES/Digit_Rounding)
* 'digitroundingZ' refers to the code of this repo.
* PSNR: peask signal noise to ratio
* Max Relative Error: max error of the point-wise relative error
* Compressed Data Size: in Bytes.
* Compression Ratio: Original Size / Compressed Size

<font size=5>The slight difference (around 1% in general) on compression ratio might be due to different lossless compressor we used: we are using Zlib while the orginal version is using Gzip embedded in HDF5. All other impelemntations should be exactly the same. <font/>

*Field: CLDLOW_1_1800_3600*
<figure class="image">
  <figcaption>Figure 1: Visualization of CESM Climate data: CLDLOW field</figcaption>
  <img align="center" width="360" src="https://www.mcs.anl.gov/~shdi/download/digitroundingZ/CLDLOW_1_1800_3600.dat2.png">
</figure>

|	| PSNR ||	Max Relative Error	||	Compressed Data Size	||	Compression Ratio	||
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| nsd | Original DR	| digitroundingZ |	Original DR	| digitroundingZ |	Original DR |	digitroundingZ |	Original DR |	digitroundingZ |
| 2 |	52.587367	| 52.587367	| 0.041659 | 0.041659 | 2057702	| 2084242	| 12.6	| 12.44 |
| 3	| 70.655662	| 70.655662	| 0.004308 | 0.004308 | 4813880	| 4944725	| 5.385	| 5.24 |
| 4	| 94.736202	| 94.736202	| 0.000402 | 0.000402 | 7918834	| 8095942	| 3.274	| 3.202 |
| 5	| 112.798155| 112.798155 | 4.3E-05 | 4.3E-05| 	10029522	| 10174900	| 2.585	| 2.55 |
| 6	| 130.850663| 130.850663 | 4E-06 | 4E-06	| 12805616| 	12942513	| 2.0243	| 2.003 |

*Field: CLDHGH_1_1800_3600*
<figure class="image">
  <figcaption>Figure 2: Visualization of CESM Climate data: CLDGHG field</figcaption>
  <img align="center" width="360" src="https://www.mcs.anl.gov/~shdi/download/digitroundingZ/CLDHGH_1_1800_3600.dat2.png">
</figure>

|	| PSNR |	|	Max Relative Error	| |	Compressed Data Size	| |	Compression Ratio	| |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| nsd | Original DR	| digitroundingZ |	Original DR	| digitroundingZ |	Original DR |	digitroundingZ |	Original DR |	digitroundingZ |
| 2	| 53.276963	| 53.276963	| 0.041659	| 0.041659	| 2257978	| 2293301	| 11.48	| 11.30| 
| 3	| 71.344325	| 71.344325	| 0.004309	| 0.004309	| 5348641	| 5516942	| 4.85	| 4.7|
| 4	| 95.405864	| 95.405864	| 0.000373	| 0.000373	| 8540314	| 8779464	| 3.04	| 2.95|
| 5	| 113.466171	| 113.466171	| 4.3E-05	| 4.3E-05	| 10734906	| 10926706	| 2.41	| 2.37|
| 6	| 131.537219	| 131.537219	| 4E-06	| 4E-06	| 13789233	| 13972567	| 1.88	| 1.86|

*Field: FLDSC_1_1800_3600*
<figure class="image">
  <figcaption>Figure 3: Visualization of CESM Climate data: FLDSC field</figcaption>
  <img align="center" width="360" src="https://www.mcs.anl.gov/~shdi/download/digitroundingZ/FLDSC_1_1800_3600.dat2.png">
</figure>

|	| PSNR |	|	Max Relative Error	| |	Compressed Data Size	| |	Compression Ratio	| |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| nsd | Original DR	| digitroundingZ |	Original DR	| digitroundingZ |	Original DR |	digitroundingZ |	Original DR |	digitroundingZ |
| 2 |	43.550814	| 43.550814	| 0.038461	| 0.038461	| 443337	| 439280	| 58.47	| 	59.01	| 
| 3	| 61.643026	| 61.643026	| 0.004854	| 0.004854	| 1544039	| 1555061		| 16.79	| 	16.67	| 
| 4	| 85.719864	| 85.719864	| 0.000305	| 0.000305	| 3529672	| 3586386		| 7.34	| 	7.23	| 
| 5	| 103.785617 | 103.785617	| 3.8E-05	| 3.8E-05	| 6259030	| 6468341		| 4.14	| 	4.01	| 
| 6	| 121.841095 | 121.841095	| 5E-06		| 5E-06		| 9212984		| 9437212		| 2.81		| 2.75	| 

*Field: PHIS_1_1800_3600*
<figure class="image">
  <figcaption>Figure 4: Visualization of CESM Climate data: PHIS field</figcaption>  
  <img align="center" width="360" src="https://www.mcs.anl.gov/~shdi/download/digitroundingZ/PHIS_1_1800_3600.dat2.png">
</figure>

|	| PSNR |	|	Max Relative Error	| |	Compressed Data Size	| |	Compression Ratio	| |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| nsd | Original DR	| digitroundingZ |	Original DR	| digitroundingZ |	Original DR |	digitroundingZ |	Original DR |	digitroundingZ |
| 2	| 60.610304	| 60.610304	| 0.041662	| 0.041662	| 6589954	| 6708593	| 3.93	| 3.86| 
| 3	| 78.677604	| 78.677604	| 0.004847	| 0.004847	| 9577066	| 9687883	| 2.706	| 2.676| 
| 4	| 96.734807	| 96.734807	| 0.000488	| 0.000488	| 12056128	| 12184078	| 2.15	| 2.13| 
| 5	| 114.879124	| 114.879124	| 4.4E-05	| 4.4E-05	| 14973718	| 15112585	| 1.73	| 1.72| 
| 6	| 138.863992	| 138.863992	| 5E-06	| 5E-06	| 17608066	| 17705056	| 1.4721	| 1.46| 
