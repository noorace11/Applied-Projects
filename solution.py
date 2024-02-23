"""
Project 6
CSE 331 S22 (Onsay)
Andrew McDonald and Aaron Jonckheere
solution.py
"""

from typing import TypeVar, List, Tuple, Generator

T = TypeVar("T")
HashNode = TypeVar("HashNode")
HashTable = TypeVar("HashTable")

# Pylint disable functions and reasons.
# pylint: disable=R1719 # Stinky pylint yelling at me for using ternary operator smh
# pylint: disable=E0102 # Pylint being weird about class definitions.

class HashNode:
    """
    Implements a hashnode object.

    Properties
    - key: [str] lookup key of hashnode
    - value: [T] lookup value associated to key
    """
    __slots__ = ["key", "value"]

    def __init__(self, key: str, value: T) -> None:
        """
        Constructs a hashnode object.
        DO NOT EDIT.

        Time: O(1)
        Space: O(1)

        :param key: [str] lookup key of hashnode.
        :param value: [T] lookup value associated to key.
        """
        self.key: str = key
        self.value: T = value

    def __str__(self) -> str:
        """
        Represents the HashNode as a string.
        DO NOT EDIT.

        Time: O(1)
        Space: O(1)

        :return: [str] String representation of the hashnode.
        """
        return f"HashNode({self.key}, {self.value})"

    __repr__ = __str__  # alias the repr operator to call str https://stackoverflow.com/a/14440577

    def __eq__(self, other: HashNode) -> bool:
        """
        Implement the equality operator to compare HashNode objects.
        DO NOT EDIT.

        Time: O(1)
        Space: O(1)

        :param other: [HashNode] hashnode we are comparing with this one.
        :return: [bool] True if equal, False if not.
        """
        return self.key == other.key and self.value == other.value


class HashTable:
    """
    Implements a hashtable for fast insertion and lookup.
    Maintains ordering such that iteration returns items in the order they were inserted.
    Inspired by Raymond Hettinger's proposed implementation @
    https://code.activestate.com/recipes/578375/.
    Quoting from Raymond Hettinger,

        The current memory layout for dictionaries is unnecessarily inefficient.
        It has a sparse table of 24-byte entries containing
        the hash value, key pointer, and value pointer.
        Instead, the 24-byte entries should be stored in a
        dense table referenced by a sparse table of indices.
        For example, the dictionary:

        d = {'timmy': 'red', 'barry': 'green', 'guido': 'blue'}

        is currently stored as:

        entries = [['--', '--', '--'],
                   [-8522787127447073495, 'barry', 'green'],
                   ['--', '--', '--'],
                   ['--', '--', '--'],
                   ['--', '--', '--'],
                   [-9092791511155847987, 'timmy', 'red'],
                   ['--', '--', '--'],
                   [-6480567542315338377, 'guido', 'blue']]

        Instead, the data should be organized as follows:

        indices =  [None, 1, None, None, None, 0, None, 2]
        entries =  [[-9092791511155847987, 'timmy', 'red'],
                    [-8522787127447073495, 'barry', 'green'],
                    [-6480567542315338377, 'guido', 'blue']]

    Properties
    - indices: [list] a table into which keys are hashed, storing the
                      index of the associated value in self.entries
    - entries: [list] a table onto which values are appended, and
                      referenced by integers in indices
    - prime_index: [int] index of current prime in Hashtable.PRIMES
    - capacity: [int] length of self.indices
    - size: [int] number of entries in self.entries
    """
    __slots__ = ["indices", "entries", "prime_index", "capacity", "size"]

    # set constants
    FREE = -1
    DELETED = -2
    PRIMES = (
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83,
        89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
        181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277,
        281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389,
        397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
        503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617,
        619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739,
        743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859,
        863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991,
        997)

    def __init__(self, capacity: int = 8) -> None:
        """
        Initializes HashTable.
        DO NOT EDIT.

        Time: O(c) where c = capacity
        Space: O(c) where c = capacity

        :param capacity: [int] Starting capacity of the hashtable,
                               i.e., starting length of the indices table.
        """
        # create underlying data structures
        self.indices: List[int] = [self.FREE] * capacity  # a sparse table of indices
        self.entries: List[HashNode] = []  # a dense table of HashNodes
        self.capacity: int = capacity
        self.size: int = 0
        # set prime index for hash computations
        i = 0
        while HashTable.PRIMES[i] <= self.capacity:
            i += 1
        self.prime_index: int = i - 1

    def __eq__(self, other: HashTable) -> bool:
        """
        Implement the equality operator to compare HashTable objects.
        DO NOT EDIT.

        Time: O(c + s) where c = capacity and s = size
        Space: O(c + s) where c = capacity and s = size

        :param other: [HashTable] hashtable we are comparing with this one.
        :return: [bool] True if equal, False if not.
        """
        if self.capacity != other.capacity or self.size != other.size:
            return False
        # the following line allows the underlying structure of the hashtables
        # to differ, as long as the items in each table are equivalent
        return list(self.items()) == list(other.items())

    def __str__(self) -> str:
        """
        Represents the HashTable as a string.
        DO NOT EDIT.

        Time: O(c + s) where c = capacity and s = size
        Space: O(c + s) where c = capacity and s = size

        :return: [str] String representation of the hashtable.
        """
        representation = [f"Size: {self.size}\nCapacity: {self.capacity}\nIndices: ["]
        for i in range(self.capacity):
            action = "FREE" if self.indices[i] == self.FREE \
                else "DELETED" if self.indices[i] == self.DELETED \
                else f'{self.indices[i]}: {self.entries[self.indices[i]]}'
            representation.append(f"[{i}]: " + action)
        representation.append("]\nEntries: [")
        for i in range(self.size):
            representation.append(f"[{i}]: {self.entries[i]}")
        representation.append("]")
        return "\n".join(representation)

    __repr__ = __str__  # alias the repr operator to call str https://stackoverflow.com/a/14440577

    def __len__(self):
        """
        Returns number of elements in the hashtable.
        DO NOT EDIT.

        Time: O(1)
        Space: O(1)

        :return: [int] Number of elements in the hashtable.
        """
        return self.size

    def _hash_1(self, key: str) -> int:
        """
        Converts a key into an initial bin number for double probing.
        DO NOT EDIT.

        Time: O(1)
        Space: O(1)

        :param key: [str] Key to be hashed.
        :return: [int] Initial bin number for double probing, None if key is an empty string.
        """
        if not key:
            return None
        hashed_value = 0

        for char in key:
            hashed_value = 181 * hashed_value + ord(char)
        return hashed_value % self.capacity

    def _hash_2(self, key: str) -> int:
        """
        Converts a key into a step size for double probing.
        DO NOT EDIT.

        Time: O(1)
        Space: O(1)

        :param key: [str] Key to be hashed.
        :return: [int] Double probing step size, None if key is an empty string.
        """
        if not key:
            return None
        hashed_value = 0

        for char in key:
            hashed_value = 181 * hashed_value + ord(char)

        prime = HashTable.PRIMES[self.prime_index]
        hashed_value = prime - (hashed_value % prime)
        if hashed_value % 2 == 0:
            hashed_value += 1
        return hashed_value

    ###############################################################################################
    # IMPLEMENT BELOW
    ###############################################################################################

    def _hash(self, key: str, inserting: bool = False) -> int:
        """
        Find an appropriate index for the inputted key using double hashing.

        Double hashing formula: index = (h1(key) + i*h2(key) % (self.size))

        Parameters:
        -----------
            key (str): The key will be hashed via double hashing to generate an index.
            inserting (bool): If the algorithm should look for the next available spot.

        Returns:
        --------
            index (int): What index self.indices is FREE or DELETED or refers to a HashNode at
                         self.entries[self.index[index]]
        """
        i = 0
        while i < self.capacity:
            # Double hashing algorithm
            index = (self._hash_1(key) + (i * self._hash_2(key))) % self.capacity
            i += 1
            # Inserting means to find the first FREE, DELETED, or matching entry.
            if inserting:
                if (self.indices[index] in {self.FREE, self.DELETED}
                        or 0 <= self.indices[index] < len(self.entries) and
                        self.entries[self.indices[index]].key == key):
                    return index
            # Otherwise, look for an instance of the HashNode specified by the key or where the first FREE spot is.
            elif (0 <= self.indices[index] < len(self.entries) and self.entries[self.indices[index]].key == key
                  or self.indices[index] == self.FREE):
                return index

        return index

    def _insert(self, key: str, value: T) -> None:
        """
        Insert a HashNode built from the key and value parameters into the HashTable

        Parameters:
        -----------
            key (str): The key that will be stored in the HashNode. Used to look up the HashNode in other functions.
            value (T): The value that will be stored in the HashNode.

        Returns:
        --------
            None
        """
        # First, check for a simple overwrite.
        position = self._hash(key)
        if 0 <= self.indices[position] < self.size and self.entries[self.indices[position]].key == key:
            self.entries[self.indices[position]] = HashNode(key=key, value=value)
            return None

        # Load factor and growing call checks.
        load_factor = (self.size + 1) / self.capacity
        if load_factor >= 0.5:
            self._grow()

        # If all else fails, find a good location and insert there.
        position = self._hash(key, inserting=True)
        self.indices[position] = self.size
        # Increment size.
        self.size += 1
        # Create HashNode and add to entries
        self.entries.append(HashNode(key=key, value=value))

    def _get(self, key: str) -> HashNode:
        """
        Find a HashNode with a key value of <key>

        Parameters:
        -----------
            key (str): The specified key being looked for within a HashNode.

        Returns:
        --------
            node (HashNode): The HashNode being searched for. If not found, then None.
        """

        node = None
        pos = self._hash(key)
        # Check if the node was found, otherwise it will stay as None.
        if self.indices[pos] not in {self.FREE, self.DELETED}:
            node = self.entries[self.indices[pos]]

        return node

    def _delete(self, key: str) -> None:
        """
        Delete a HashNode from the HashTable.

        Returns:
        --------
            (bool): None if no node was deleted, otherwise True.
        """
        pos = self._hash(key)
        if self.indices[pos] not in {self.FREE, self.DELETED}:
            # Delete the node at the found index. Update applicable values.
            self.entries[self.indices[pos]] = None
            self.indices[pos] = self.DELETED
            self.size -= 1
            return True

        return None

    def _grow(self) -> None:
        """
        Double the capacity of the existing HashTable.

        Returns:
        --------
            None
        """
        # Make the capacity twice as big.
        self.capacity *= 2
        # Initialize every new bucket as FREE
        self.indices = [self.FREE] * self.capacity
        old_entries = self.entries[:]
        self.entries.clear()
        # Start from the old prime index and recalculate.
        i = self.prime_index
        while self.PRIMES[i] <= self.capacity:
            i += 1
        self.prime_index = i - 1
        # Rehash and reinsert
        self.size = 0
        for node in old_entries:
            self._insert(node.key, node.value)

    def __setitem__(self, key: str, value: T) -> None:
        """
        Magic function for standard python syntax of "self[key] = value".

        Parameters:
        -----------
            key (str): The specified key that will identify the new HashNode.
            value (T): The value of the new HashNode.

        Returns:
        --------
            None
        """
        self._insert(key, value)

    def __getitem__(self, key: str) -> T:
        """
        Magic function for standard python syntax of "self[key]".

        Parameters:
        -----------
            key (str): The specified key that will identify the HashNode.

        Raises:
        -------
            KeyError: if the HashNode is not present inside the HashTable.

        Returns:
        --------
            node.value (T): That value of the HashNode corresponding to the key.
        """
        node = self._get(key)
        if node:
            return node.value

        raise KeyError(f'Node with key value {key} not present in HashTable.')

    def __delitem__(self, key: str) -> None:
        """
        Magic function for standard python syntax of "del self[key]".

        Parameters:
        -----------
            key (str): The specified key that will identify the HashNode to be deleted.

        Raises:
        -------
            KeyError: if the HashNode is not present inside the HashTable.

        Returns:
        --------
           None
        """
        # Did it done do it??
        done_it = self._delete(key)
        if not done_it:
            raise KeyError(f'Node with key value {key} not present in HashTable.')

    def __contains__(self, key: str) -> bool:
        """
        Magic function for standard python syntax of "key in self".

        Parameters:
        -----------
            key (str): The specified key that will identify the HashNode to identify within
                        the HashTable.

        Returns:
        --------
           (bool): True if the HashNode is a member of the HashTable, otherwise False.
        """
        return True if self._get(key) else False

    def update(self, pairs: List[Tuple[str, T]]) -> None:
        """
        Updates the HashTable with an iterable of key, value pairs.

        Parameters:
        -----------
            pairs (List[Tuple[str, T]]): list of tuples (key, value) being updated.

        Returns:
        --------
            None
        """
        # Insert every key value pair within pairs.
        for key, value in pairs:
            self._insert(key, value)

    def keys(self, reverse: bool = False) -> Generator[str, None, None]:
        """
        Generate all the keys in the HashTable.

        Parameters:
        -----------
            reverse (bool): yield generator in reverse order if True.

        Yields:
        -------
            (Generator[str, None, None]): A generator object of keys.
        """
        if reverse:
            for i in range(self.size - 1, -1, -1):
                if self.entries[i]:
                    yield self.entries[i].key
        else:
            for i in range(self.size):
                if self.entries[i]:
                    yield self.entries[i].key

    def values(self, reverse: bool = False) -> Generator[T, None, None]:
        """
        Generate all the values in the HashTable.

        Parameters:
        -----------
            reverse (bool): yield generator in reverse order if True.

        Yields:
        -------
            (Generator[str, None, None]): A generator object of all values.
        """
        if reverse:
            #  Throw that range in rotation. 💃
            for i in range(self.size - 1, -1, -1):
                if self.entries[i]:
                    yield self.entries[i].value
        else:
            # Normie range.
            for i in range(self.size):
                if self.entries[i]:
                    yield self.entries[i].value

    def items(self, reverse: bool = False) -> Generator[Tuple[str, T], None, None]:
        """
        Generate all the values in the HashTable.

        Parameters:
        -----------
            reverse (bool): yield generator in reverse order if True.

        Yields:
        -------
            (Generator[Tuple[str, T], None, None]): A generator object of all key-value pairs.
        """
        for key, value in zip(self.keys(reverse), self.values(reverse)):
            yield key, value

    def clear(self) -> None:
        """
        Clear the HashTable of all HashNodes.
        """
        self.entries.clear()
        self.size = 0
        self.indices = [self.FREE] * self.capacity


class DiscordDestroyer:
    """
    Implements a DiscordDestroyer post management system.
    It will be far better than Discord, Destroying Discord in the long run.
    This is only the beginning.

    Properties
    - posts_by_id: Hashtable mapping id strings to post strings
    - ids_by_user: Hashtable mapping user strings to list of Hashtable of posts from that user
    - post_id_seed: Starting value for post id
    """
    __slots__ = ["posts_by_id", "ids_by_user", "post_id_seed"]

    def __init__(self):
        """
        Initializes DiscordDestroyer class.
        DO NOT EDIT.

        Time: O(1)
        Space: O(1)

        :return: None
        """
        self.posts_by_id: HashTable = HashTable()
        self.ids_by_user: HashTable = HashTable()
        self.post_id_seed: int = 0

    def generate_post_id(self, user: str, message: str) -> str:
        """
        Creates a unique post id for each post.
        DO NOT EDIT.

        Time: O(1)
        Space: O(1)

        :return: [str] post id for the post.
        """
        post_id = hash(user + message + str(self.post_id_seed))
        self.post_id_seed += 1
        return str(post_id)

    ###############################################################################################
    # IMPLEMENT BELOW
    ###############################################################################################

    def post(self, user: str, message: str) -> str:
        """
        Post It! Spew your thoughts on the interwebs for strangers to judge!

        Update the posts_by_id hashtable and the ids_by_user hashtable.

        Parameters:
        -----------
            user (str): The username of the poster.
            message (str): What the user would like to post.

        Returns:
        --------
            post_id (str): A unique id to go with the new post.
        """
        code = self.generate_post_id(user, message)
        post_id = ','.join((user, code))
        self.posts_by_id[post_id] = message
        # If the user has not been seen before, add in a new HashTable specific to their username.
        if user not in self.ids_by_user:
            self.ids_by_user[user] = HashTable()
        # Set the message.
        self.ids_by_user[user][code] = message

        return post_id

    def delete_post(self, user_post_id: str) -> bool:
        """
        Delete It! Uh oh. Did too many strangers dislike your post? ಥ_ಥ That's okay.
        We can delete it and pretend it never happened. (｡･∀･)ﾉﾞ
        Because nothing on the internet is forever, right?

        Removes the post with provided post_id from posts_by_id and ids_by_user hashtables.

        Parameters:
        -----------
            user_post_id (str): The unique post id that will help find the post to be deleted.

        Returns:
        --------
            (bool): True if the post was deleted, otherwise False.
        """
        try:
            del self.posts_by_id[user_post_id]
            user, post_id = user_post_id.split(',')
            del self.ids_by_user[user][post_id]
        except KeyError:
            # Key was not present
            return False
        else:
            return True

    def get_most_recent_posts(self, v: int) -> Generator[Tuple[str, str], None, None]:
        """
        Check It! Obsessively recheck the feed's most recent posts 🆒 😎 💯.

        Parameters:
        -----------
            v (int): How many posts you'd like to pull.
        Yields:
        --------
            (Generator[Tuple[str, str], None, None]): A generator of the user
                    and their respective post.
        """
        for post_num, post_bundle in enumerate(self.posts_by_id.items(reverse=True)):
            # Have we hit the max posts?
            if post_num == v:
                break
            post_id, message = post_bundle
            yield post_id.split(',')[0], message

    def get_posts_by_user(self, user: str) -> Generator[Tuple[str, str], None, None]:
        """
        Review It! Need to see how much clout you've obtained? Nothing is more important than
        fake internet points. Keep checking up on those fire posts you've made. 🔥 👃

        Parameters:
        -----------
            user (str): The user to pull all posts from.

        Yields:
        --------
            (Generator[Tuple[str, str], None, None]): A generator of the user and their posts.

        Returns:
        --------
            (list): [] if the user is not in the database.
        """
        # Is the user in the database?
        if user not in self.ids_by_user:
            return []
            # Please don't strike me down for using return and yield in the same function 🥺
            # I couldn't "yield None" because that would have been [None] and failed the test case.
        for post in self.ids_by_user[user].values():
            yield user, post
