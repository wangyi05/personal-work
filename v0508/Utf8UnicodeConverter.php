<?php


/**
 * 
 * http://www.randomchaos.com/documents/?source=php_and_unicode
 * 
 * How to develop multilingual, Unicode applications with PHP
 * 
 * By Scott Reynen
 * 
 * First, let's go over the absolute minimum every PHP developer absolutely, positively must know about 
 * Unicode and character sets:
 * 
 * 1. Unicode represents all characters (in all languages) with integers.
 * 2. UTF-8 is a decent character set for mapping characters to integers.
 *
 * Some would say PHP has little or no Unicode support, and they'd be right. But I refer you back to the 
 * first item on our absolute minimum list. It's all just integers, and PHP has plenty of support for integers, 
 * so we can work around this problem.
 * 
 * You set UTF-8 as your character set in your (X)HTML, right? If not, go do that. I'm not going to explain HTML 
 * here, because this is a PHP guide. Okay, now that you've done that, your users will be posting content 
 * through <input type="text"> and <textarea> fields. Anything that's in English will work normally, so let's not 
 * worry about that. Anything else will be split up into multiple characters before it gets to our PHP code. So 
 * the first thing we need to do is cram it all back into a single number, representing its Unicode value. 
 * 
 */
 

/**
 * 
 * class Utf8UnicodeConverter
 * Wrapper class for Scott Reynen's functions
 * Add by YYU
 *
 */ 
class Utf8UnicodeConverter {

	/**
	 * 
	 * Utf8UnicodeConverter constructor
	 * @author YYu
	 *
	 */ 
	function Utf8UnicodeConverter() {}

	/**
	 * 
	 * UTF-8 to Unicode
	 *  
	 * The following function will take any text submitted through a UTF-8 encoded form and return it as 
	 * a list of Unicode values.
	 * 
	 * @author Scott Reynen
	 * @param string $str
	 * @return array $unicode
	 * 
	 */
	function utf8_to_unicode( $str ) {
		$unicode = array();
		$values = array();
		$lookingFor = 1;
		for ($i = 0; $i < strlen( $str ); $i++ ) {
			$thisValue = ord( $str[ $i ] );
			if ( $thisValue < 128 ) $unicode[] = $thisValue;
			else {
				if ( count( $values ) == 0 ) $lookingFor = ( $thisValue < 224 ) ? 2 : 3;
				$values[] = $thisValue;
				if ( count( $values ) == $lookingFor ) {
					$number = ( $lookingFor == 3 ) ?
					( ( $values[0] % 16 ) * 4096 ) + ( ( $values[1] % 64 ) * 64 ) + ( $values[2] % 64 ):
					( ( $values[0] % 32 ) * 64 ) + ( $values[1] % 64 );
					$unicode[] = $number;
					$values = array();
					$lookingFor = 1;
				} // if
			} // if
		} // for
		return $unicode;
	} // utf8_to_unicode
	
	/**
	 * 
	 * Convert unicode to HTML entities
	 * 
	 * This one's easy because HTML character entities allow you to specify a character by its Unicode value. 
	 * The following function will convert a Unicode array to a string of HTML character entities.
	 * 
	 * @author Scott Reynen, modified by YYu
	 * @param array $unicode
	 * @return string $entities
	 * 
	 */
	
	function unicode_to_entities( $unicode ) {
		$entities = '';
		foreach( $unicode as $value ) {
			//$entities .= '&#' . $value . ';';  // SR
			$entities .= '&#x' . strtoupper(dechex($value)) . ';'; // YY
		}
		return $entities;
	} // unicode_to_entities
	
	/**
	 * 
	 * Strip Tags
	 * 
	 * To strip all HTML tags from the user's text before you print it, PHP has a handy strip_tags() function. 
	 * Wouldn't it be nice if we could just use that? Well, we can. strip_tags(), like most of PHP's functions, 
	 * assumes you are sending it ASCII text. So we just need to send it ASCII text. We can do this by changing 
	 * the previous function so that it converts those characters that fall within the ASCII character range 
	 * back to their original characters, rather than their Unicode entities.
	 * 
	 * @author Scott Reynen
	 * @param array $unicode
	 * @return string $entities
	 * 
	 */
	
	function unicode_to_entities_preserving_ascii( $unicode ) {
		$entities = '';
		foreach( $unicode as $value ) {
			$entities .= ( $value > 127 ) ? '&#' . $value . ';' : chr( $value );
		} //foreach
		return $entities;
	} // unicode_to_entities_preserving_ascii
	
	/**
	 * 
	 * Now, we can run the results of this function through strip_tags() and it will work just how we expect 
	 * it to. This same technique will work for many other PHP functions, but let's move on to a scenario 
	 * where this won't work, and see how we can work around it.
	 * 
	 * String Positions
	 * 
	 * So we have some text in an unknown language that we've converted to Unicode values, and we want to 
	 * find where some other text, say "42", is within that text. We can't use the previous methods because 
	 * Unicode entities takes up more than one character (plus the number "42" might be part of one of our 
	 * Unicode values). So what we're going to do instead is rewrite PHP's strpos() function to work with 
	 * our Unicode arrays.
	 * 
	 * This function works exactly like PHP's strpos() function, only we pass it Unicode value arrays instead 
	 * of strings for both $haystack and $needle. For example, we might call it like so:
	 *
	 * @example $position = strpos_unicode( $unicode , utf8_to_unicode( '42' ) );
	 * 
	 */
	
	function strpos_unicode( $haystack , $needle , $offset = 0 ) {
		$position = $offset;
		$found = FALSE;
		while( (! $found ) && ( $position < count( $haystack ) ) ) {
			if ( $needle[0] == $haystack[$position] ) {
				for ($i = 1; $i < count( $needle ); $i++ ) {
					if ( $needle[$i] != $haystack[ $position + $i ] ) break;
				} // for
				if ( $i == count( $needle ) ) {
					$found = TRUE;
					$position--;
				} // if
			} // if
			$position++;
		} // while
		return ( $found == TRUE ) ? $position : FALSE;
	} // strpos_unicode
	
	/**
	 * 
	 * Unicode to UTF-8
	 * 
	 * Since this article was first published, a reader emailed me asking: How would I convert from the Unicode 
	 * values back to actual characters? The following function will convert a Unicode array back to its UTF-8 
	 * representation.
	 * 
	 * @author Scott Reynen
	 * @param array $str (unicode array)
	 * @return string $utf8
	 * 
	 */
	
	function unicode_to_utf8( $str ) {
		$utf8 = '';
		foreach( $str as $unicode ) {
			if ( $unicode < 128 ) {
				$utf8.= chr( $unicode );
			} elseif ( $unicode < 2048 ) {
				$utf8.= chr( 192 +  ( ( $unicode - ( $unicode % 64 ) ) / 64 ) );
				$utf8.= chr( 128 + ( $unicode % 64 ) );
			} else {
				$utf8.= chr( 224 + ( ( $unicode - ( $unicode % 4096 ) ) / 4096 ) );
				$utf8.= chr( 128 + ( ( ( $unicode % 4096 ) - ( $unicode % 64 ) ) / 64 ) );
				$utf8.= chr( 128 + ( $unicode % 64 ) );
			} // if
		} // foreach
		return $utf8;
	} // unicode_to_utf8

}


?>

