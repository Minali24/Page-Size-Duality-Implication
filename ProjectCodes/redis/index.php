
<?php
/*With HugePages
Write Time: 43.298053979874
Read Time: 37.420018911362
Total Time: 80.718072891235

Without HugePage
Write Time: 37.756885051727
Read Time: 41.841183900833
Total Time: 79.59806895256
*/
	echo "Php working<br>";
	//Connecting to Redis server on localhost
	$redis = new Redis();
	$redis->connect('127.0.0.1', 6379);
	echo "Connection to server sucessfully <br>";
	//check whether server is running or not
	echo "Server is running: ".$redis->ping()."<br>";

	$i=0;
	$start_time = microtime(true);
	echo "Start Time: ".$start_time."<br>";
	for ($i=0; $i<1000000; $i++)
	{
	    $redis->set($i, "5325354353454353465768789909807556754634523513455532535435345435346576878990980755675463452351345553253543534543534657687899098075567546345235134555325354353454353465768789909807556754634523513455532535435345435346576878990980755675463452351345553253543534543534657687899098075567546345235134555325354353454353465768789909807556754634523513455532535435345435346576878990980755675463452351345553253543534543534657687899098075567546345235134555325354353454353465768789909807556754634523513455");
	   
	}
	$write_time = microtime(true);
	echo "Write Time: ".($write_time-$start_time)."<br>";
	
	$rand = 0;

	for ($i=0; $i<1000000; $i++)
	{
	    $rand = rand(0,1000000);
	   
	   // Get the stored data and print it
	   $temp = $redis->get($i);
	}
	$read_time = microtime(true);
	echo "Read Time: ".($read_time -$write_time)."<br>";
	$total_time = $read_time - $start_time;
	echo "Total Time: ".$total_time."<br>";
	//echo timeDiff($now,new microtime());

?>

