public static List<Integer> getResultList(Searcher searcher, TopDocs docs,
		int first, int max) throws CorruptIndexException, IOException {
	List<Integer> list = new ArrayList<Integer>(max);
	ScoreDoc[] hits = docs.scoreDocs;
	if (first < 0) {
		first = 0;
	}
	if (max < 0) {
		max = 0;
	}
	int last = first + max;
	int len = hits.length;
	if (last > len) {
		last = len;
	}
	for (int i = first; i < last; i++) {
		Document d = searcher.doc(hits[i].doc);
		list.add(Integer.valueOf(d.getField(ID).stringValue()));
	}
	return list;
}
