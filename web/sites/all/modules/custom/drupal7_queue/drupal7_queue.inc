<?php

//Simulates a bunch of data that could come from a remote source.
function remoteData() {
  return [
    ['title' => 'Sample Item 1', 'type' => 'article'],
    ['title' => 'Sample Item 2', 'type' => 'article'],
    ['title' => 'Sample Item 3', 'type' => 'article'],
    ['title' => 'Sample Item 4', 'type' => 'article'],
    ['title' => 'Sample Item 5', 'type' => 'article'],
  ];
}

function createItemQueue() {
  $queue = DrupalQueue::get('drupalTutQueue');
  
  foreach (remoteData() as $item) {
    watchdog('notice', 'create item run');
    $queue->createItem($item);
  }
}

//Very basic example, just convert the items into nodes.
function saveRemoteItem($item) {
  $node = (object) $item;
  node_save($node);
  return !empty($node->nid);
}
