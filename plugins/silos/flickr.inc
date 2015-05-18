<?php
/**
 * @file
 * Silo implementation as ctools plugin.
 *
 * Create a Flickr App
 * @see https://www.flickr.com/services/apps/create/
 */

// Ctools plugin definition.
$plugin = array(
  'title' => 'Flickr',
  'class' => 'FlickrSilo',
);

/**
 * Class FlickrSilo.
 */
class FlickrSilo extends Silo {

  protected $title = 'Flickr';

  public function authenticate() {
    parent::authenticate();

    try {
      $this->token = $this->storage->retrieveAccessToken($this->title);
    }
    catch(Exception $e) {
      if (!empty($_GET['oauth_token'])) {
        $this->token = $this->storage->retrieveAccessToken($this->title);

        // This was a callback request from remote, get the token.
        $this->service->requestAccessToken(
          $_GET['oauth_token'],
          $_GET['oauth_verifier'],
          $this->token->getRequestTokenSecret()
        );
      }
      else {
        // Extra request needed for oauth1 to request a request token
        $this->token = $this->service->requestRequestToken();
        $url = $this->service->getAuthorizationUri(
          array('oauth_token' => $this->token->getRequestToken(), 'perms' => 'write')
        );
        header('Location: ' . $url);
      }
    }
  }

}
