# Robotica

come parla la raspby con la teensy

//input 
    //L:100,R:100,0
        //100 sono valori di velocita
        //0 rappresenta i cubi da 1 a x che puo buttare giu
    //STOP
        //dopo aver mandato lo stop la teensy si blocca e aspetta uno stop di AK dalla raspby
    //START
        //dopo aver mandato lo start la teensy si blocca e aspetta uno start di AK dalla raspby
    
//output 
    //L:0,F:1,R:0,B:
        //i 3 sensori di calore 0=freddo 1=caldo
        //la B e il nero sotto puo essere 0 nulla 1 nero 2 checkpoint, il checkpoin piu recente e quello che riparti se ti incricchi
    //STOP
        //lo mando quando spegno con lo switch per dire mi sono incriccato
    //START
        //partenza

se cercate la libreria per i driver pololu che vada bene andate alla directory 
