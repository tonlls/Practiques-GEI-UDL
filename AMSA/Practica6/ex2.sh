#loops for 10s
for i in {1..10}
do
    #sleep for 1s
    sleep 1
    #calculate free swap memory
    swap_free=$(free | grep Swap | awk '{print $4}')
    #calculate percentage of free swap memory
    swap_percent=$(echo "scale=2; $swap_free / $swap_total * 100" | bc)
    #if swap is less than 10% create a swap file
    if [ $swap_percent -lt 10 ]
    then
        #create swap file
        fallocate -l 1G /swapfile
        #set permissions
        chmod 600 /swapfile
        #set label
        mkswap /swapfile
        #enable swap
        swapon /swapfile
    fi

    #print percentage of free swap memory
    echo "Swap free: $swap_percent%"
done