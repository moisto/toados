<html>
<head>
<title>ISBN SCRAPER</title>

<style type="text/css">
body {
	background: #3030cc;
	color: #eee;
	font-family: courier, mono;
	font-size: 0.7 em;
	white-space: pre-wrap;
}

form {
	margin, padding: 0;
}
</style>

</head>

<body>

<div id="blah">Loading...</div>

<?php


	function scrape_book($isbn) {

		set_time_limit(0);
		
		$url = "http://openisbn.com/search.php?q=" . $isbn . "&isbn=1&ei=utf-8&qtype=all&fr=sfp";

		$tendigit = "";

		$page = "";
		while (!$page = file_get_contents($url)) {};
		
		// deal with the redirect...
		
		$url = explode("0;url=", $page);
		$url = explode("\">", $url[1]);
		$url = trim($url[0]);
		
		$page = "";
		while (!$page = file_get_contents($url)) {};

		$tendigit = explode('/', $url);
		$tendigit = $tendigit[count($tendigit)-2];

		return $tendigit;


		
		/*
		$title = explode(" - OPENISBN Project:Download Book Data</title>", $page);
		$title = explode(" - ", $title[0]);
		$title = $title[1];
		
		$subject = explode("<BR>Category: ", $page);
		$subject = explode("<BR>", $subject[1]);
		$subject = strip_tags(trim($subject[0], " ,"));
		
		if (!$title)
			$title = "?";

		// If the title has no subject information...
		if (!$subject) {
			// Resort to collecting the keywords associated with the title...
			$subject = explode("</a><BR>Keywords: ", $page);
			$subject = explode("<BR>", $subject[1]);
			$subject = "(" . strip_tags(trim($subject[0], " ,")) . ")";
			$subject = str_replace("&amp;", "&", $subject); // turns &amp; into actual ampersands

			if ($subject == "()") // Still nothing? Just forget about finding a subject...
				$subject = "?";
		}
		
		
		if ($isbn && $title && $subject) {
			
			$entry = $tendigit . "\t". strtoupper(substr($title, 0, 45)) . "\t" . $subject . "\n";
			$file = file_put_contents("./detailed10.txt", $entry, FILE_APPEND);
			//echo $entry;
		}
		*/
		
	}

	// BEGIN WEBPAGE HERE...
	
	//error_reporting(0);
	
	//$file = file_get_contents("october_onhand.txt");
	$file = file_get_contents("september_onhand.txt");
	$file = explode(PHP_EOL, $file);
	$len = count($file);


		
	// start from: 0
	// stopped at: 783
	// stopped at: 1082
	//$len = 3;
	//$jump = 20;


	$i = $_GET['startfrom'];


	for ($i = 0; $i < $len; $i++) {
		$isbn = explode("\t", $file[$i]);
		$isbn = $isbn[0];

		$tendigit = scrape_book($isbn);

		if (strlen($tendigit)) {
			file_put_contents("10digit_september.txt", $tendigit . "\t" . $isbn[1] . "\t" . $isbn[2]);
			echo "
				<script language=\"javascript\">document.getElementById('blah').innerHTML = 'Loading... " . ($i/$len)*100 . "%';
				</script>";
		}
	}




//	echo "</pre>\n";
	
//	echo "<p>COMPLETED!</p>\n";

?>

</body>

</html>
