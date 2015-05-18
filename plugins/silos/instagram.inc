<?php
/**
 * @file
 * Silo implementation as ctools plugin.
 *
 * Create a Instagram App
 * @see https://instagram.com/developer/clients/manage/
 */

// Ctools plugin definition.
$plugin = array(
  'title' => 'Instagram',
  'class' => 'InstagramSilo',
);

/**
 * Class InstagramSilo.
 */
class InstagramSilo extends Silo {

  protected $title = 'Instagram';

  protected $scopes = array('basic', 'comments', 'relationships', 'likes');

  public function authenticate() {
    parent::authenticate();

    try {
      $this->token = $this->storage->retrieveAccessToken($this->title);
    }
    catch (Exception $e) {
      if (!empty($_GET['code'])) {
        // This was a callback request from remote, get the token.
        $this->service->requestAccessToken($_GET['code']);
      }
      else {
        $url = $this->service->getAuthorizationUri();
        header('Location: ' . $url);
      }
    }
  }

}
