import shutil
import os
    
source_dir = 'D:\GitHub\Practiques-GEI-UDL\Algoritmica_i_Complexitat'
target_dir = 'D:\GEI\2n\algoritmica\TonLlucia'
    
file_names = os.listdir(source_dir)
    
for file_name in file_names:
    shutil.copy(os.path.join(source_dir, file_name), target_dir)