# Geiraze

Geiraze is an 8 bit compression algorithm that works by abbreviating character pairs using an inner dictionary.

## Methods:

**Compression:**

1. We scan the file looking for valid character pairs. As we find pairs, we save them in an array.

2. Once we finish reading the file, we look into the other array. As we walk into the array, we code each pair using Geiraze dictionary, and data is then saved into a string.

3. Finally, we write the content of the final string to the file.

**Extraction:**

1. We read each data packet in file, we unjoin pairs, and save them into another array.

2. We write the content of the final array to a file.
