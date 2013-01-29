if [[ $# < 3 ]]; then
  echo "Usage: $0 <input_dir> <first> <second>"
  exit 1
fi

OUTPUT_DIR=`mktemp -d`
INPUT_DIR=$1

FIRST=$2
SECOND=$3
IFS="
"
for TEST_CASE in `command ls -1 $INPUT_DIR`; do
  FIRST_OUT=$OUTPUT_DIR"/"$TEST_CASE".first"
  SECOND_OUT=$OUTPUT_DIR"/"$TEST_CASE".second"

  $FIRST < $TEST_CASE > $FIRST_OUT
  $SECOND < $TEST_CASE > $SECOND_OUT
  
  diff $FIRST_OUT $SECOND_OUT > /dev/null
  
  if [[ $? ]]; then
	echo -n "Entering inspection shell"
	cd $OUTPUT_DIR
	$SHELL
	rm -rf $OUTPUT_DIR
	break
  fi
done
