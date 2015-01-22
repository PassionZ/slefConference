# while read HOST USER PASS  
#do  
     
#    echo "$HOST"  
#    echo "$USER" 
#    echo "$PASS"
#done <Server

while HOST=$(line)  
do   
    echo "LINE:"$HOST  
done <  Server 

HOST = `cat UPSERVER`
echo "////////////"
    echo $HOST
    echo $USER
    echo $PASS


cat Server | while read HOST USER PASS
do
 
    echo "$HOST"
    echo "$USER"
    echo "$PASS"
done 

echo "////////////"
    echo $HOST
    echo $USER
    echo $PASS

