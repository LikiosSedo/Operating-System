/**
 * This class generates page references ranging from 0 .. 9
 *
 * Usage: PageGenerator gen = new PageGenerator() int[] ref =
 * gen.getReferenceString();
 */

public class PageGenerator {
	private static final int DEFAULT_SIZE = 100;
	private static final int RANGE = 9;

	int[] referenceString;

	public PageGenerator() {
		this(DEFAULT_SIZE);
	}

	public PageGenerator(int count) {
		if (count < 0)
			throw new IllegalArgumentException();

		java.util.Random generator = new java.util.Random();
		referenceString = new int[count];

		for (int i = 0; i < count; i++)
			referenceString[i] = generator.nextInt(RANGE + 1);
	}

	public int[] getReferenceString() {
		//int[] str = { 7, 2, 3, 1, 2, 5, 3, 4, 6, 7, 7, 1, 0, 5, 4, 6, 2, 3, 0, 1 }; //9.21 FIFO LRU 3
		//int[] str = { 1, 2, 3, 4, 5, 3, 4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2 };//9.30 FIFO 4

		//return str;
		return referenceString;
	}
}