<?php

//Simulates a bunch of data that could come from a remote source.
function createItemQueue() {
  $queue = DrupalQueue::get('drupalTutQueue');
  $link = 'http://aginius.local/api/formations.json';
  $i = 0;
  $stop_get = 0;

  do {
    $request = drupal_http_request(addToURL('page', $i, $link));
    if ($request->code == 200) {
      $data_decode = json_decode($request->data);
      if (count($data_decode)) {
        $queue->createItem($data_decode);
      } else {
        $stop_get++;
      }
      $i++;
    } else {
      $stop_get++;
    }
  } while ( $stop_get < 2 );
  exit;
}

//Very basic example, just convert the items into nodes.
function saveRemoteItem($item) {
  $node = (object) $item->data;
  node_save($node);
  return !empty($node->nid);
}

function saveRemoteData() {
  //Get the queue so we can add to it.  Use a
  //descriptive name. It's ok if it doesn't exist yet.
  $queue = DrupalQueue::get('drupalTutQueue');

  //Pull items out one at a time.
  while ($item = $queue->claimItem()) {

    //Try saving the data.
    if (saveRemoteItem($item)) {
      //Good, we succeeded.  Delete the item as it is no longer needed.
//      $queue->deleteItem($item);
      watchdog('notice', 'Node ' . $item->data['title'] . ' is created.');
    }
    else {
      watchdog('error', 'Item in queue can\'t save');
    }
  }
}

/**
 * @param $key
 * @param $value
 * @param $url
 * @return string
 */
function addToURL($key, $value, $url) {
  $info = parse_url( $url );
  $query = [];

  if (isset($info['query'])) {
    parse_str($info['query'], $query );
  }

  return $info['scheme'] . '://' . $info['host'] . $info['path'] . '?' . http_build_query($query ? array_merge($query, [$key => $value]) : [$key => $value]);
}