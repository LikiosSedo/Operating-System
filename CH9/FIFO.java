/**
 * This class implements the FIFO page-replacement strategy.
 *
 */

public class FIFO extends ReplacementAlgorithm {
	// FIFO list of page frames
	private FIFOList frameList;

	/**
	 * @param pageFrameCount - the number of physical page frames
	 */
	public FIFO(int pageFrameCount) {
		super(pageFrameCount);
		frameList = new FIFOList(pageFrameCount);
	}

	/**
	 * insert a page into a page frame.
	 * 
	 * @param int pageNumber - the page number being inserted.
	 */
	public void insert(int pageNumber) {
		if (!frameList.search(pageNumber)) { // if page fault
			pageFaultCount++; // page fault count plus one
			frameList.insert(pageNumber); // FIFO insert
		}
	}

	class FIFOList {
		// the page frame list
		int[] pageFrameList;

		// the number of elements in the page frame list
		int elementCount;

		FIFOList(int pageFrameCount) {
			pageFrameList = new int[pageFrameCount];

			// we initialize each entry to -1 to indicate initial value is invalid
			java.util.Arrays.fill(pageFrameList, -1);
			elementCount = 0;
		}

		/**
		 * @param pageNumber the number of the page to be inserted into the page frame
		 *                   list.
		 */
		void insert(int pageNumber) {
			pageFrameList[elementCount] = pageNumber; // insert
			if (elementCount != pageFrameCount - 1) { // FIFO
				elementCount++;
			} else {
				elementCount = 0;
			}
			dump();
			System.out.println();
		}

		// dump the page frames
		void dump() {
			for (int i = 0; i < pageFrameList.length; i++)
				System.out.print("[" + i + "]" + pageFrameList[i] + ", ");
		}

		/**
		 * Searches for page pageNumber in the page frame list
		 * 
		 * @return true if pageNumber was found
		 * @return false if pageNumber was not found
		 */
		boolean search(int pageNumber) {
			boolean returnVal = false;

			for (int i = 0; i < pageFrameList.length; i++) {
				if (pageNumber == pageFrameList[i]) {
					returnVal = true;
					break;
				}
			}
			return returnVal;
		}
	}
}