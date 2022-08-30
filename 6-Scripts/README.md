# SCRIPTS
These are scripts to run on rk3399 and process your result on PC
* for rk3399, you may wish to run the xxScan shell script within working_dir_template folder to evaluate, be sure the corresponding folders are created,
and you have installed the meter driver, we provide a template called genFolder for the folders.
* for pc, you may wish to copy the resulting csv from rk3399 and draw results, we provide template for line and bar, and pleas change the
file name of csv in genTogether.py for different evaluation. The python version for them is 3.9, and we require the matplotlibpy.
# Important Notes
Make sure all configuration files in working_dir_template is loaded correctly, or you can not set up or run