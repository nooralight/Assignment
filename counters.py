String s = "one two three two three three";
String[] sArr = s.split(" ");
 
long startTime = 0;
long endTime = 0;
long duration = 0;
 
// naive approach
startTime = System.nanoTime();
HashMap<String, Integer> counter = new HashMap<String, Integer>();
 
for (int i = 0; i < 1000000; i++)
	for (String a : sArr) {
		if (counter.containsKey(a)) {
			int oldValue = counter.get(a);
			counter.put(a, oldValue + 1);
		} else {
			counter.put(a, 1);
		}
	}
 
endTime = System.nanoTime();
duration = endTime - startTime;
System.out.println("Naive Approach :  " + duration);
 
// better approach
startTime = System.nanoTime();
HashMap<String, MutableInteger> newCounter = new HashMap<String, MutableInteger>();
 
for (int i = 0; i < 1000000; i++)
	for (String a : sArr) {
		if (newCounter.containsKey(a)) {
			MutableInteger oldValue = newCounter.get(a);
			oldValue.set(oldValue.get() + 1);
		} else {
			newCounter.put(a, new MutableInteger(1));
		}
	}
 
