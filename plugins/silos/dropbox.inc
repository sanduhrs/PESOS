<?php
/**
 * @file
 * Silo implementation as ctools plugin.
 *
 * Create a Dropbox App
 * @see https://www.dropbox.com/developers/apps
 */

// Ctools plugin definition.
$plugin = array(
  'title' => 'Dropbox',
  'class' => 'DropboxSilo',
);

/**
 * Class DropboxSilo.
 */
class DropboxSilo extends Silo {

  protected $title = 'Dropbox';

  protected $scopes = array();

  public function connect() {
    parent::connect();

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
